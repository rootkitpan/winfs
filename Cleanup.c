#include "fs_common.h"

// https://learn.microsoft.com/en-us/windows-hardware/drivers/ifs/irp-mj-cleanup
// handle reached 0

NTSTATUS DispatchCleanup(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	BOOLEAN TopLevel;
	
	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] IRP_MJ_CLEANUP in\n");

	if (DeviceObject == gCDO) {
		DbgPrint("[Fat32] %s Our CDO\n", __func__);

		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = 0;

		IoCompleteRequest(Irp, IO_DISK_INCREMENT);

		DbgPrint("[Fat32] IRP_MJ_CLEANUP out\n");

		return STATUS_SUCCESS;
	}

	
	
	
	
	
	FsRtlEnterFileSystem();

	if ( IoGetTopLevelIrp() == NULL ) {
		IoSetTopLevelIrp( Irp );
		TopLevel = TRUE;
	} else {
		TopLevel = FALSE;
	}
	
	
	
	
	{
		PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
		PVCB Vcb;
		PFCB Fcb;
		PCCB Ccb;
		ULONG Type;
		
		DecodeFileObject(IrpSp->FileObject, &Type, &Vcb, &Fcb, &Ccb);
		
		if(Type == UNKNOWN_FILE_OBJECT){
			// for volume mount IoCreateStreamFileObject TODO
			// VCB FCB CCB not set for VirtualVolumeFile when it was created
			DbgPrint("[Fat32] Type == UNKNOWN_FILE_OBJECT \n");
			Irp->IoStatus.Status = STATUS_SUCCESS;
			Irp->IoStatus.Information = 0;
			IoCompleteRequest(Irp, IO_NO_INCREMENT);
			
		} else {
			DbgPrint("[Fat32] Type = %d \n", Type);
			Irp->IoStatus.Status = STATUS_SUCCESS;
			Irp->IoStatus.Information = 0;
			IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}
	}
	
	
	
	
	if (TopLevel) {
		IoSetTopLevelIrp( NULL );
	}
	
	FsRtlExitFileSystem();

	DbgPrint("[Fat32] IRP_MJ_CLEANUP out\n");

	return STATUS_SUCCESS;
}
