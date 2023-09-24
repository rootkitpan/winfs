#include "fs_common.h"

static FAST_IO_DISPATCH FastIo;
FS_DATA FsData;


static BOOLEAN Fat32AcquireForReadAheadNoOp(
	PVOID Fcb,
	BOOLEAN Wait
)
{
	UNREFERENCED_PARAMETER(Fcb);
	UNREFERENCED_PARAMETER(Wait);

	DbgPrint("[Fat32] Fat32AcquireForReadAheadNoOp\n");

	IoSetTopLevelIrp((PIRP)FSRTL_CACHE_TOP_LEVEL_IRP);

	return TRUE;
}

static VOID Fat32ReleaseFromReadAheadNoOp(
	PVOID Fcb
)
{
	UNREFERENCED_PARAMETER(Fcb);

	DbgPrint("[Fat32] Fat32ReleaseFromReadAheadNoOp\n");

	IoSetTopLevelIrp(NULL);
}


static BOOLEAN Fat32AcquireForLazyWriteNoOp(
	PVOID Fcb,
	BOOLEAN Wait
)
{
	UNREFERENCED_PARAMETER(Fcb);
	UNREFERENCED_PARAMETER(Wait);

	DbgPrint("[Fat32] Fat32AcquireForLazyWriteNoOp\n");

	IoSetTopLevelIrp((PIRP)FSRTL_CACHE_TOP_LEVEL_IRP);

	return TRUE;
}

static VOID Fat32ReleaseFromLazyWriteNoOp(
	PVOID Fcb
)
{
	UNREFERENCED_PARAMETER(Fcb);

	DbgPrint("[Fat32] Fat32ReleaseFromLazyWriteNoOp\n");

	IoSetTopLevelIrp(NULL);
}



VOID Fat32Unload(PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	if (FsData.CDO) {
		IoDeleteDevice(FsData.CDO);
	}
}


NTSTATUS DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS Status = STATUS_SUCCESS;
	UNICODE_STRING DeviceName;

	UNREFERENCED_PARAMETER(RegistryPath);

	// dispatch
	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CREATE_NAMED_PIPE] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_READ] = DispatchRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SET_INFORMATION] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_QUERY_EA] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SET_EA] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_FLUSH_BUFFERS] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_QUERY_VOLUME_INFORMATION] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SET_VOLUME_INFORMATION] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_DIRECTORY_CONTROL] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL] = DispatchFileSystemControl;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_LOCK_CONTROL] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = DispatchCleanup;
	DriverObject->MajorFunction[IRP_MJ_CREATE_MAILSLOT] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_QUERY_SECURITY] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SET_SECURITY] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_POWER] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CHANGE] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_QUERY_QUOTA] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_SET_QUOTA] = DispatchCommon;
	DriverObject->MajorFunction[IRP_MJ_PNP] = DispatchPnp;


	// fastio
	RtlIsZeroMemory(&FastIo, sizeof(FAST_IO_DISPATCH));
	FastIo.SizeOfFastIoDispatch = sizeof(FAST_IO_DISPATCH);
	FastIo.FastIoCheckIfPossible = FastIoCheckIfPossible;
	FastIo.FastIoRead = FastIoRead;
	FastIo.FastIoWrite = FastIoWrite;
	FastIo.FastIoQueryBasicInfo = FastIoQueryBasicInfo;
	FastIo.FastIoQueryStandardInfo = FastIoQueryStandardInfo;
	FastIo.FastIoLock = FastIoLock;
	FastIo.FastIoUnlockSingle = FastIoUnlockSingle;
	FastIo.FastIoUnlockAll = FastIoUnlockAll;
	FastIo.FastIoUnlockAllByKey = FastIoUnlockAllByKey;
	FastIo.FastIoDeviceControl = FastIoDeviceControl;
	//FastIo.AcquireFileForNtCreateSection = FastIoAcquireFile;
	FastIo.ReleaseFileForNtCreateSection = FastIoReleaseFile;
	FastIo.FastIoDetachDevice = FastIoDetachDevice;
	FastIo.FastIoQueryNetworkOpenInfo = FastIoQueryNetworkOpenInfo;
	FastIo.AcquireForModWrite = FastIoAcquireForModWrite;
	FastIo.MdlRead = FastIoMdlRead;
	FastIo.MdlReadComplete = FastIoMdlReadComplete;
	FastIo.PrepareMdlWrite = FastIoPrepareMdlWrite;
	FastIo.MdlWriteComplete = FastIoMdlWriteComplete;
	FastIo.FastIoReadCompressed = FastIoReadCompressed;
	FastIo.FastIoWriteCompressed = FastIoWriteCompressed;
	FastIo.MdlReadCompleteCompressed = FastIoMdlReadCompleteCompressed;
	FastIo.MdlWriteCompleteCompressed = FastIoMdlWriteCompleteCompressed;
	FastIo.FastIoQueryOpen = FastIoQueryOpen;
	FastIo.ReleaseForModWrite = FastIoReleaseForModWrite;
	FastIo.AcquireForCcFlush = FastIoAcquireForCcFlush;
	FastIo.ReleaseForCcFlush = FastIoReleaseForCcFlush;
	DriverObject->FastIoDispatch = &FastIo;
	
	{
		// use PreAcquireForSectionSynchronization in FS_FILTER_CALLBACKS
		// instead of AcquireFileForNtCreateSection in FastIO
		FS_FILTER_CALLBACKS FilterCallbacks;
		
		RtlZeroMemory( &FilterCallbacks, sizeof(FS_FILTER_CALLBACKS) );
		FilterCallbacks.SizeOfFsFilterCallbacks = sizeof(FS_FILTER_CALLBACKS);
		FilterCallbacks.PreAcquireForSectionSynchronization = FilterCallbackAcquireForCreateSection;
		Status = FsRtlRegisterFileSystemFilterCallbacks(
				DriverObject,
				&FilterCallbacks );
		if(Status != STATUS_SUCCESS){
			DbgPrint("[Fat32] FsRtlRegisterFileSystemFilterCallbacks failed, status = 0x%08X\n", Status);
			return Status;
		}
	}

	//unload
	DriverObject->DriverUnload = Fat32Unload;

	// create file system device object(CDO / FsDO)
	RtlInitUnicodeString(&DeviceName, L"\\TestFat32");
	Status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_DISK_FILE_SYSTEM,
		0,
		FALSE,
		&FsData.CDO);
	if (Status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] IoCreateDevice failed, status = 0x%08X\n", Status);
		return Status;
	}
	DbgPrint("[Fat32] CDO = %p\n", FsData.CDO);



	// init FsData
	ExInitializeResourceLite( &FsData.Resource );
	FsData.CacheManagerNoOpCallbacks.AcquireForReadAhead = &Fat32AcquireForReadAheadNoOp;
	FsData.CacheManagerNoOpCallbacks.ReleaseFromReadAhead = &Fat32ReleaseFromReadAheadNoOp;
	FsData.CacheManagerNoOpCallbacks.AcquireForLazyWrite = &Fat32AcquireForLazyWriteNoOp;
	FsData.CacheManagerNoOpCallbacks.ReleaseFromLazyWrite = &Fat32ReleaseFromLazyWriteNoOp;
	
	
	
	IoRegisterFileSystem(FsData.CDO);
	ObReferenceObject(FsData.CDO);

	DbgPrint("[Fat32] DriverEntry ok\n");

	return Status;
}


/*
* use DriverMonitor.exe to start driver
* use DebugView to see log
* 
* disable UEFI secure boot feature in BIOS
* bcdedit /set testsigning on
* bcdedit /set testsigning off
* 
* sizeof(ULONG) == 4
* 
* C:\Windows\minidump
* 
* file system resources are acquired first
* Then Cache Manager resources are acquired
* Finally, Memory Manager resources are acquired
* 
* 
* create VHD
* edit VHD to make the fat fs fail to mount the disk
* edit the VHD and use the *.vhd file in the below
* C:\Users\rootkitpan\AppData\Local\VirtualStore
* 
* 
* VM:
* bcdedit /debug on
* bcdedit /dbgsettings debugport:1 baudrate:115200
* 
* Add serial
* \\.\pipe\com1
* This end is server
* the other end is app
* Delete printer, since it will occupy the serial 1
* 
* Host
* File --> Kernel Debug --> COM
* check pipe and reconnect
* set pipe to \\.\pipe\com1
* 
*/
