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


typedef struct _FAT_DATA {
	PDEVICE_OBJECT FsDO;
	ERESOURCE Resource;
	CACHE_MANAGER_CALLBACKS CacheManagerCallbacks;
	CACHE_MANAGER_CALLBACKS CacheManagerNoOpCallbacks;
} FAT_DATA, *PFAT_DATA;


// IRP Major Function
DRIVER_DISPATCH Fat32Common;
DRIVER_DISPATCH Fat32Create;
DRIVER_DISPATCH Fat32Close;
DRIVER_DISPATCH Fat32FileSystemControl;
DRIVER_DISPATCH Fat32Cleanup;
DRIVER_DISPATCH Fat32Pnp;

// Fast IO
FAST_IO_CHECK_IF_POSSIBLE Fat32FastIoCheckIfPossible;
FAST_IO_READ Fat32FastIoRead;
FAST_IO_WRITE Fat32FastIoWrite;
FAST_IO_QUERY_BASIC_INFO Fat32FastIoQueryBasicInfo;
FAST_IO_QUERY_STANDARD_INFO Fat32FastIoQueryStandardInfo;
FAST_IO_LOCK Fat32FastIoLock;
FAST_IO_UNLOCK_SINGLE Fat32FastIoUnlockSingle;
FAST_IO_UNLOCK_ALL Fat32FastIoUnlockAll;
FAST_IO_UNLOCK_ALL_BY_KEY Fat32FastIoUnlockAllByKey;
FAST_IO_DEVICE_CONTROL Fat32FastIoDeviceControl;
FAST_IO_ACQUIRE_FILE Fat32AcquireFileForNtCreateSection;
FAST_IO_RELEASE_FILE Fat32ReleaseFileForNtCreateSection;
FAST_IO_DETACH_DEVICE Fat32FastIoDetachDevice;
FAST_IO_QUERY_NETWORK_OPEN_INFO Fat32FastIoQueryNetworkOpenInfo;
FAST_IO_ACQUIRE_FOR_MOD_WRITE Fat32FastIoAcquireForModWrite;
FAST_IO_MDL_READ Fat32FastIoMdlRead;
FAST_IO_MDL_READ_COMPLETE Fat32FastIoMdlReadComplete;
FAST_IO_PREPARE_MDL_WRITE Fat32FastIoPrepareMdlWrite;
FAST_IO_MDL_WRITE_COMPLETE Fat32FastIoMdlWriteComplete;
FAST_IO_READ_COMPRESSED Fat32FastIoReadCompressed;
FAST_IO_WRITE_COMPRESSED Fat32FastIoWriteCompressed;
FAST_IO_MDL_READ_COMPLETE_COMPRESSED Fat32FastIoMdlReadCompleteCompressed;
FAST_IO_MDL_WRITE_COMPLETE_COMPRESSED Fat32FastIoMdlWriteCompleteCompressed;
FAST_IO_QUERY_OPEN Fat32FastIoQueryOpen;
FAST_IO_RELEASE_FOR_MOD_WRITE Fat32FastIoReleaseForModWrite;
FAST_IO_ACQUIRE_FOR_CCFLUSH Fat32FastIoAcquireForCcFlush;
FAST_IO_RELEASE_FOR_CCFLUSH Fat32FastIoReleaseForCcFlush;



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



extern FAT_DATA FatData;

#endif /* _FS_COMMON_H_ */
