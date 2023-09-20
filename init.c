#include "fs_common.h"

static FAST_IO_DISPATCH FastIo;
FAT_DATA FatData;


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

	if (FatData.FsDO) {
		IoDeleteDevice(FatData.FsDO);
	}
}


NTSTATUS DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING DeviceName;

	UNREFERENCED_PARAMETER(RegistryPath);

	// dispatch
	DriverObject->MajorFunction[IRP_MJ_CREATE] = Fat32Create;
	DriverObject->MajorFunction[IRP_MJ_CREATE_NAMED_PIPE] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Fat32Close;
	DriverObject->MajorFunction[IRP_MJ_READ] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SET_INFORMATION] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_QUERY_EA] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SET_EA] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_FLUSH_BUFFERS] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_QUERY_VOLUME_INFORMATION] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SET_VOLUME_INFORMATION] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_DIRECTORY_CONTROL] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL] = Fat32FileSystemControl;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_LOCK_CONTROL] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = Fat32Cleanup;
	DriverObject->MajorFunction[IRP_MJ_CREATE_MAILSLOT] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_QUERY_SECURITY] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SET_SECURITY] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_POWER] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CHANGE] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_QUERY_QUOTA] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_SET_QUOTA] = Fat32Common;
	DriverObject->MajorFunction[IRP_MJ_PNP] = Fat32Pnp;


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
	FastIo.AcquireFileForNtCreateSection = AcquireFileForNtCreateSection;
	FastIo.ReleaseFileForNtCreateSection = ReleaseFileForNtCreateSection;
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

	//unload
	DriverObject->DriverUnload = Fat32Unload;

	// create file system device object(CDO / FsDO)
	RtlInitUnicodeString(&DeviceName, L"\\TestFat32");
	status = IoCreateDevice(DriverObject,
		0,
		&DeviceName,
		FILE_DEVICE_DISK_FILE_SYSTEM,
		0,
		FALSE,
		&FatData.FsDO);
	if (status != STATUS_SUCCESS) {
		DbgPrint("[Fat32] IoCreateDevice failed, status = 0x%08X\n", status);
		return status;
	}
	DbgPrint("[Fat32] FsDO = %p\n", FatData.FsDO);



	// init FatData
	ExInitializeResourceLite( &FatData.Resource );
	FatData.CacheManagerNoOpCallbacks.AcquireForReadAhead = &Fat32AcquireForReadAheadNoOp;
	FatData.CacheManagerNoOpCallbacks.ReleaseFromReadAhead = &Fat32ReleaseFromReadAheadNoOp;
	FatData.CacheManagerNoOpCallbacks.AcquireForLazyWrite = &Fat32AcquireForLazyWriteNoOp;
	FatData.CacheManagerNoOpCallbacks.ReleaseFromLazyWrite = &Fat32ReleaseFromLazyWriteNoOp;
	
	
	
	IoRegisterFileSystem(FatData.FsDO);
	ObReferenceObject(FatData.FsDO);

	DbgPrint("[Fat32] DriverEntry ok\n");

	return status;
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
