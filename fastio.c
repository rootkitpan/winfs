#include "fs_common.h"


// PFAST_IO_CHECK_IF_POSSIBLE
BOOLEAN FastIoCheckIfPossible (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	BOOLEAN Wait,
	ULONG LockKey,
	BOOLEAN CheckForReadOperation,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);

	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(CheckForReadOperation);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_READ
BOOLEAN FastIoRead (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	BOOLEAN Wait,
	ULONG LockKey,
	PVOID Buffer,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_WRITE
BOOLEAN FastIoWrite (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	BOOLEAN Wait,
	ULONG LockKey,
	PVOID Buffer,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_QUERY_BASIC_INFO
BOOLEAN FastIoQueryBasicInfo (
	PFILE_OBJECT FileObject,
	BOOLEAN Wait,
	PFILE_BASIC_INFORMATION Buffer,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_QUERY_STANDARD_INFO
BOOLEAN FastIoQueryStandardInfo (
	PFILE_OBJECT FileObject,
	BOOLEAN Wait,
	PFILE_STANDARD_INFORMATION Buffer,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_LOCK
BOOLEAN FastIoLock (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	PLARGE_INTEGER Length,
	PEPROCESS ProcessId,
	ULONG Key,
	BOOLEAN FailImmediately,
	BOOLEAN ExclusiveLock,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(Key);
	UNREFERENCED_PARAMETER(FailImmediately);
	UNREFERENCED_PARAMETER(ExclusiveLock);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_UNLOCK_SINGLE
BOOLEAN FastIoUnlockSingle (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	PLARGE_INTEGER Length,
	PEPROCESS ProcessId,
	ULONG Key,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(Key);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}



// PFAST_IO_UNLOCK_ALL
BOOLEAN FastIoUnlockAll (
	PFILE_OBJECT FileObject,
	PEPROCESS ProcessId,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_UNLOCK_ALL_BY_KEY
BOOLEAN FastIoUnlockAllByKey (
	PFILE_OBJECT FileObject,
	PVOID ProcessId,
	ULONG Key,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(ProcessId);
	UNREFERENCED_PARAMETER(Key);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_DEVICE_CONTROL
BOOLEAN FastIoDeviceControl (
	PFILE_OBJECT FileObject,
	BOOLEAN Wait,
	PVOID InputBuffer,
	ULONG InputBufferLength,
	PVOID OutputBuffer,
	ULONG OutputBufferLength,
	ULONG IoControlCode,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(InputBuffer);
	UNREFERENCED_PARAMETER(InputBufferLength);
	UNREFERENCED_PARAMETER(OutputBuffer);
	UNREFERENCED_PARAMETER(OutputBufferLength);
	UNREFERENCED_PARAMETER(IoControlCode);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_ACQUIRE_FILE - AcquireFileForNtCreateSection
// obsolete
VOID FastIoAcquireFile (PFILE_OBJECT FileObject)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
}

NTSTATUS FilterCallbackAcquireForCreateSection (
	PFS_FILTER_CALLBACK_DATA CallbackData,
	PVOID *CompletionContext
)
{
	DbgPrint("[Fat32][FilterCB] %s in\n", __func__);

	UNREFERENCED_PARAMETER(CallbackData);
	UNREFERENCED_PARAMETER(CompletionContext);
	
	return STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY;
}


// PFAST_IO_RELEASE_FILE - ReleaseFileForNtCreateSection
VOID FastIoReleaseFile (PFILE_OBJECT FileObject)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
}


// PFAST_IO_DETACH_DEVICE
VOID FastIoDetachDevice (
	PDEVICE_OBJECT SourceDevice,
	PDEVICE_OBJECT TargetDevice
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(SourceDevice);
	UNREFERENCED_PARAMETER(TargetDevice);
}


// PFAST_IO_QUERY_NETWORK_OPEN_INFO
BOOLEAN FastIoQueryNetworkOpenInfo (
	PFILE_OBJECT FileObject,
	BOOLEAN Wait,
	PFILE_NETWORK_OPEN_INFORMATION Buffer,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(Wait);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_ACQUIRE_FOR_MOD_WRITE - AcquireForModWrite
NTSTATUS FastIoAcquireForModWrite (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER EndingOffset,
	PERESOURCE *ResourceToRelease,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(EndingOffset);
	UNREFERENCED_PARAMETER(ResourceToRelease);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_MDL_READ - MdlRead
BOOLEAN FastIoMdlRead (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	ULONG LockKey,
	PMDL *MdlChain,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_MDL_READ_COMPLETE - MdlReadComplete
BOOLEAN FastIoMdlReadComplete (
	PFILE_OBJECT FileObject,
	PMDL MdlChain,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_PREPARE_MDL_WRITE - PrepareMdlWrite
BOOLEAN FastIoPrepareMdlWrite (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	ULONG LockKey,
	PMDL *MdlChain,
	PIO_STATUS_BLOCK IoStatus,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_MDL_WRITE_COMPLETE - MdlWriteComplete
BOOLEAN FastIoMdlWriteComplete (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	PMDL MdlChain,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_READ_COMPRESSED
BOOLEAN FastIoReadCompressed (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	ULONG LockKey,
	PVOID Buffer,
	PMDL *MdlChain,
	PIO_STATUS_BLOCK IoStatus,
	PCOMPRESSED_DATA_INFO CompressedDataInfo,
	ULONG CompressedDataInfoLength,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(CompressedDataInfo);
	UNREFERENCED_PARAMETER(CompressedDataInfoLength);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_WRITE_COMPRESSED
BOOLEAN FastIoWriteCompressed (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	ULONG Length,
	ULONG LockKey,
	PVOID Buffer,
	PMDL *MdlChain,
	PIO_STATUS_BLOCK IoStatus,
	PCOMPRESSED_DATA_INFO CompressedDataInfo,
	ULONG CompressedDataInfoLength,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(Length);
	UNREFERENCED_PARAMETER(LockKey);
	UNREFERENCED_PARAMETER(Buffer);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(IoStatus);
	UNREFERENCED_PARAMETER(CompressedDataInfo);
	UNREFERENCED_PARAMETER(CompressedDataInfoLength);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_MDL_READ_COMPLETE_COMPRESSED - MdlReadCompleteCompressed
BOOLEAN FastIoMdlReadCompleteCompressed (
	PFILE_OBJECT FileObject,
	PMDL MdlChain,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_MDL_WRITE_COMPLETE_COMPRESSED - MdlWriteCompleteCompressed
BOOLEAN FastIoMdlWriteCompleteCompressed (
	PFILE_OBJECT FileObject,
	PLARGE_INTEGER FileOffset,
	PMDL MdlChain,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(FileOffset);
	UNREFERENCED_PARAMETER(MdlChain);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_QUERY_OPEN
BOOLEAN FastIoQueryOpen (
	PIRP Irp,
	PFILE_NETWORK_OPEN_INFORMATION NetworkInformation,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(Irp);
	UNREFERENCED_PARAMETER(NetworkInformation);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_RELEASE_FOR_MOD_WRITE - ReleaseForModWrite
NTSTATUS FastIoReleaseForModWrite (
	PFILE_OBJECT FileObject,
	PERESOURCE ResourceToRelease,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(ResourceToRelease);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_ACQUIRE_FOR_CCFLUSH - AcquireForCcFlush
NTSTATUS FastIoAcquireForCcFlush (
	PFILE_OBJECT FileObject,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}


// PFAST_IO_RELEASE_FOR_CCFLUSH - ReleaseForCcFlush
NTSTATUS FastIoReleaseForCcFlush (
	PFILE_OBJECT FileObject,
	PDEVICE_OBJECT DeviceObject
)
{
	DbgPrint("[Fat32][FastIO] %s in\n", __func__);
	
	UNREFERENCED_PARAMETER(FileObject);
	UNREFERENCED_PARAMETER(DeviceObject);

	return FALSE;
}

