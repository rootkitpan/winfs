#include "fs_common.h"


static NTSTATUS InitializeVcb(
	PVCB Vcb,
	PVPB Vpb,
	PDEVICE_OBJECT TargetDeviceObject)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	RtlZeroMemory(Vcb, sizeof(VCB));

	Vcb->VolumeFileHeader.NodeTypeCode = FAT_NTC_VCB;
	Vcb->VolumeFileHeader.NodeByteSize = sizeof(VCB);
	
	Vcb->TargetDeviceObject = TargetDeviceObject;
	Vcb->RealDevice = Vpb->RealDevice;
	Vcb->Vpb = Vpb;

	Vcb->VirtualVolumeFile = IoCreateStreamFileObject(NULL, Vpb->RealDevice);
	if (Vcb->VirtualVolumeFile == NULL) {
		DbgPrint("[Fat32] IoCreateStreamFileObject failed\n");
		return STATUS_UNSUCCESSFUL;
	}

	Vcb->VirtualVolumeFile->Vpb = Vpb;
	Vcb->VirtualVolumeFile->FsContext = Vcb;
	Vcb->VirtualVolumeFile->FsContext2 = NULL;
	Vcb->VirtualVolumeFile->SectionObjectPointer = &(Vcb->SectionObjectPointers);
	Vcb->VirtualVolumeFile->ReadAccess = TRUE;
	Vcb->VirtualVolumeFile->WriteAccess = TRUE;
	Vcb->VirtualVolumeFile->DeleteAccess = TRUE;

	try {
		CC_FILE_SIZES FileSizes;
		
		FileSizes.AllocationSize.QuadPart = sizeof(FAT32_BOOT_SECTOR);
		FileSizes.FileSize.QuadPart = sizeof(FAT32_BOOT_SECTOR);
		FileSizes.ValidDataLength.HighPart = MAXLONG;
		FileSizes.ValidDataLength.LowPart = MAXULONG;
		
		CcInitializeCacheMap(Vcb->VirtualVolumeFile,
				&FileSizes,
				TRUE,
				&FsData.CacheManagerNoOpCallbacks,
				Vcb);
	} except(EXCEPTION_EXECUTE_HANDLER) {
		status = GetExceptionCode();
		DbgPrint("[Fat32] CcInitializeCacheMap abnormal 0x%08x\n", status);
		ObDereferenceObject(Vcb->VirtualVolumeFile);
		Vcb->VirtualVolumeFile = NULL;
		return STATUS_UNSUCCESSFUL;
	}
	
	ExInitializeFastMutex(&Vcb->AdvancedFcbHeaderMutex);
	FsRtlSetupAdvancedHeader(&Vcb->VolumeFileHeader,
		&Vcb->AdvancedFcbHeaderMutex);

	return STATUS_SUCCESS;
}


NTSTATUS Fat32MapData(PVCB Vcb, PVOID *Bcb, PFAT32_BOOT_SECTOR *BootSector)
{
	LARGE_INTEGER StartingVbo;
	BOOLEAN bRet = FALSE;
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	try {
		StartingVbo.QuadPart = 0;
		bRet = CcMapData(Vcb->VirtualVolumeFile,
			&StartingVbo,
			sizeof(FAT32_BOOT_SECTOR),
			MAP_WAIT,
			Bcb,
			(PVOID*)BootSector);
		if (bRet == FALSE) {
			DbgPrint("[Fat32] CcMapData failed\n");
			return STATUS_UNSUCCESSFUL;
		}
	} except(EXCEPTION_EXECUTE_HANDLER) {
		status = GetExceptionCode();
		DbgPrint("[Fat32] CcMapData abnormal, status = 0x%X\n", status);
		return STATUS_UNSUCCESSFUL;

		// STATUS_INVALID_DEVICE_REQUEST 0xC0000010
		// STATUS_DEVICE_OFF_LINE 0x80000010
	}

	return STATUS_SUCCESS;
}

NTSTATUS Fat32MountVolume(
	PDEVICE_OBJECT DeviceObject,		// CDO
	PIRP Irp
)
{
	NTSTATUS Status;
	PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_OBJECT TargetDeviceObject = IrpSp->Parameters.MountVolume.DeviceObject;
	PVPB Vpb = IrpSp->Parameters.MountVolume.Vpb;
	PDEVICE_OBJECT RealDevice = Vpb->RealDevice;
	PDEVICE_OBJECT VDO = NULL;
	BOOLEAN WeClearedVerifyRequiredBit = FALSE;
	PVCB Vcb = NULL;
	PVOID Bcb = NULL;
	PFAT32_BOOT_SECTOR BootSector;
	
	DbgPrint("[Fat32] IRP_MN_MOUNT_VOLUME in\n");
	
	// FatScanForDismountedVcb
	
	Status = IoCreateDevice(DeviceObject->DriverObject,
			sizeof(VCB),
			NULL,
			FILE_DEVICE_DISK_FILE_SYSTEM,
			0,
			FALSE,
			&VDO);
	if (Status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] IoCreateDevice failed, 0x%08x\n", Status);
		goto fail_exit;
	}
	DbgPrint("[Fat32] VDO = %p\n", VDO);
	
	if (TargetDeviceObject->AlignmentRequirement > VDO->AlignmentRequirement) {
		VDO->AlignmentRequirement = TargetDeviceObject->AlignmentRequirement;
	}
	
	VDO->StackSize = TargetDeviceObject->StackSize + 1;
	
	{
		DISK_GEOMETRY Geometry;
		
		Status = PerformDeviceIoControl(IOCTL_DISK_GET_DRIVE_GEOMETRY,
			TargetDeviceObject,
			NULL, 0,
			&Geometry, sizeof(DISK_GEOMETRY),
			FALSE);
		if (Status != STATUS_SUCCESS) {
			DbgPrint("[Fat32] IOCTL_DISK_GET_DRIVE_GEOMETRY failed, 0x%08x\n", Status);
			goto fail_exit;
		}
		VDO->SectorSize = (USHORT)Geometry.BytesPerSector;
	}
	
	ClearFlag(VDO->Flags, DO_DEVICE_INITIALIZING);
	
	// direct IRP to our FS
	Vpb->DeviceObject = VDO;
	
	if (FlagOn(RealDevice->Flags, DO_VERIFY_VOLUME)) {
		ClearFlag(RealDevice->Flags, DO_VERIFY_VOLUME);
		WeClearedVerifyRequiredBit = TRUE;
		
		DbgPrint("[Fat32] we cleared DO_VERIFY_VOLUME flag\n");
	}
	
	ObReferenceObject(TargetDeviceObject);
	
	Vcb = (PVCB)VDO->DeviceExtension;
	Status = InitializeVcb(Vcb, Vpb, TargetDeviceObject);
	if (Status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] Initialize Vcb failed\n");
		goto fail_exit;
	}
	
	Status = Fat32MapData(Vcb, &Bcb, &BootSector);
	if (Status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] Fat32MapData failed\n");
		goto fail_exit;
	}
	
	Status = Fat32CheckBootSector(BootSector);
	if (Status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] Not Fat32 Volume\n");
		goto fail_exit;
	}
	
	Vpb->SerialNumber = BootSector->BS_VolID;

	// Unpin Data
	CcUnpinData(Bcb);
	
	// TODO
	// create RootDCB
	
	// VolumeLabel
	// Vpb->VolumeLabel
	// Vpb->VolumeLabelLength
	
	
	// remount check
	// SerialNumber
	// RealDevice
	// VolumeLabelLength   VolumeLabel
	// bpb
	
	
	
	
	Status = STATUS_SUCCESS;
	

fail_exit:
	if(Status != STATUS_SUCCESS){
		if(Bcb){
			CcUnpinData(Bcb);
		}
		if(Vcb){
			if(Vcb->VirtualVolumeFile){
				LARGE_INTEGER FatLargeZero = { 0,0 };
				CcUninitializeCacheMap(Vcb->VirtualVolumeFile, &FatLargeZero, NULL);
				FsRtlTeardownPerStreamContexts(&Vcb->VolumeFileHeader);
				
				ObDereferenceObject(Vcb->VirtualVolumeFile);
				Vcb->VirtualVolumeFile = NULL;
			}
			ObDereferenceObject(TargetDeviceObject);
			Vcb = NULL;
		}
		if(VDO){
			IoDeleteDevice(VDO);
			VDO = NULL;
		}
	}
	
	if (WeClearedVerifyRequiredBit == TRUE) {
		SetFlag(RealDevice->Flags, DO_VERIFY_VOLUME);
	}
	
	DbgPrint("[Fat32] IRP_MN_MOUNT_VOLUME out, status = %x\n", Status);
	return Status;
}



NTSTATUS Fat32UserFsRequest(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
){
	PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
	ULONG FsControlCode = IrpSp->Parameters.FileSystemControl.FsControlCode;
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] %s in\n", __FUNCTION__);

	switch (FsControlCode){
	case FSCTL_INVALIDATE_VOLUMES:
		DbgPrint("[Fat32] FSCTL_INVALIDATE_VOLUMES in\n");
		break;

	case FSCTL_DISMOUNT_VOLUME:
		DbgPrint("[Fat32] FSCTL_DISMOUNT_VOLUME in\n");
		break;

	default:
		DbgPrint("[Fat32] unknown  FsControlCode = %x\n", FsControlCode);
		break;
	}

	return status;
}




NTSTATUS DispatchFileSystemControl(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp
)
{
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION IrpSp = NULL;
	BOOLEAN TopLevel;
	
	FsRtlEnterFileSystem();
	
	if ( IoGetTopLevelIrp() == NULL ) {
		IoSetTopLevelIrp( Irp );
		TopLevel = TRUE;
	} else {
		TopLevel = FALSE;
	}

	IrpSp = IoGetCurrentIrpStackLocation(Irp);

	DbgPrint("[Fat32] %s in DeviceObject = %p\n", __func__, DeviceObject);
	

	switch (IrpSp->MinorFunction) {
	case IRP_MN_USER_FS_REQUEST:
		status = Fat32UserFsRequest(DeviceObject, Irp);
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		break;

	case IRP_MN_MOUNT_VOLUME:
		status = Fat32MountVolume(DeviceObject, Irp);

		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		break;

	default:
		DbgPrint("[Fat32] Fat32FileSystemControl unknown IRP_MN 0x%08x in\n", IrpSp->MinorFunction);
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		break;
	}

	if(TopLevel){
		IoSetTopLevelIrp( NULL );
	}
	
	FsRtlExitFileSystem();

	return status;
}


