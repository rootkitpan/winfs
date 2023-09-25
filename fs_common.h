#ifndef _FS_COMMON_H_
#define _FS_COMMON_H_

#include <ntifs.h>
#include <ntdddisk.h>


#include "DiskData.h"
#include "MemoryData.h"



// node type
#define FAT_NTC_VCB ((CSHORT)0x0701)
#define FAT_NTC_FCB ((CSHORT)0x0702)
#define FAT_NTC_DCB ((CSHORT)0x0703)
#define FAT_NTC_CCB ((CSHORT)0x0704)

#define NodeType(Ptr) (*((PCSHORT)Ptr))





typedef struct _FS_DATA {
	ERESOURCE Resource;
	CACHE_MANAGER_CALLBACKS CacheManagerCallbacks;
	CACHE_MANAGER_CALLBACKS CacheManagerNoOpCallbacks;
} FS_DATA, *PFS_DATA;


// IRP Major Function
DRIVER_DISPATCH DispatchCommon;
DRIVER_DISPATCH DispatchCreate;
DRIVER_DISPATCH DispatchClose;
DRIVER_DISPATCH DispatchRead;
DRIVER_DISPATCH DispatchFileSystemControl;
DRIVER_DISPATCH DispatchCleanup;
DRIVER_DISPATCH DispatchPnp;

// Fast IO
FAST_IO_CHECK_IF_POSSIBLE FastIoCheckIfPossible;
FAST_IO_READ FastIoRead;
FAST_IO_WRITE FastIoWrite;
FAST_IO_QUERY_BASIC_INFO FastIoQueryBasicInfo;
FAST_IO_QUERY_STANDARD_INFO FastIoQueryStandardInfo;
FAST_IO_LOCK FastIoLock;
FAST_IO_UNLOCK_SINGLE FastIoUnlockSingle;
FAST_IO_UNLOCK_ALL FastIoUnlockAll;
FAST_IO_UNLOCK_ALL_BY_KEY FastIoUnlockAllByKey;
FAST_IO_DEVICE_CONTROL FastIoDeviceControl;
FAST_IO_ACQUIRE_FILE FastIoAcquireFile;
FAST_IO_RELEASE_FILE FastIoReleaseFile;
FAST_IO_DETACH_DEVICE FastIoDetachDevice;
FAST_IO_QUERY_NETWORK_OPEN_INFO FastIoQueryNetworkOpenInfo;
FAST_IO_ACQUIRE_FOR_MOD_WRITE FastIoAcquireForModWrite;
FAST_IO_MDL_READ FastIoMdlRead;
FAST_IO_MDL_READ_COMPLETE FastIoMdlReadComplete;
FAST_IO_PREPARE_MDL_WRITE FastIoPrepareMdlWrite;
FAST_IO_MDL_WRITE_COMPLETE FastIoMdlWriteComplete;
FAST_IO_READ_COMPRESSED FastIoReadCompressed;
FAST_IO_WRITE_COMPRESSED FastIoWriteCompressed;
FAST_IO_MDL_READ_COMPLETE_COMPRESSED FastIoMdlReadCompleteCompressed;
FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED FastIoMdlWriteCompleteCompressed;
FAST_IO_QUERY_OPEN FastIoQueryOpen;
FAST_IO_RELEASE_FOR_MOD_WRITE FastIoReleaseForModWrite;
FAST_IO_ACQUIRE_FOR_CCFLUSH FastIoAcquireForCcFlush;
FAST_IO_RELEASE_FOR_CCFLUSH FastIoReleaseForCcFlush;

NTSTATUS FilterCallbackAcquireForCreateSection(
    PFS_FILTER_CALLBACK_DATA CallbackData,
    PVOID* CompletionContext
);

// disk io util
NTSTATUS PerformDeviceIoControl(
	ULONG IoControlCode,
	PDEVICE_OBJECT Device,
	PVOID InputBuffer,
	ULONG InputBufferLength,
	OUT PVOID OutputBuffer,
	ULONG OutputBufferLength,
	BOOLEAN InternalDeviceIoControl
);


// FILE_OJBECT type
#define USER_FILE				((ULONG)0)
#define USER_DIRECTORY			((ULONG)1)
#define USER_VOLUME				((ULONG)2)
#define VOLUME_STREAM_FILE		((ULONG)3)
#define DIRETORY_STREAM_FILE	((ULONG)4)



extern FS_DATA FsData;
extern PDEVICE_OBJECT gCDO;




NTSTATUS DecodeFileObject(
	PFILE_OBJECT FileObject,
	PULONG Type,
	PVCB* Vcb,
	PFCB* FcbOrDcb,
	PCCB* Ccb
);



#endif /* _FS_COMMON_H_ */


