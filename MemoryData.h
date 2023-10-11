#ifndef _MEMORY_DATA_H_
#define _MEMORY_DATA_H_

#include <ntifs.h>
#include "DiskData.h"


// Memory Allocation Tag
#define MEMTAG_FCB	('FCB ')




// node type
#define FAT_NTC_VCB ((CSHORT)0x0701)
#define FAT_NTC_FCB ((CSHORT)0x0702)
#define FAT_NTC_DCB ((CSHORT)0x0703)
#define FAT_NTC_CCB ((CSHORT)0x0704)




typedef struct _BPB_INFO{
	USHORT		BytesPerSector;
	UCHAR		SectorsPerCluster;
	UCHAR		FATCount;
	USHORT		ReservedSectorCount;
	ULONG32		TotalSectorCount;
	ULONG32		FatSizeInSector;
	ULONG32		RootFirstCluster;
	ULONG32		VolumeID;
	UCHAR		VolumeLabel[11];
} BPB_INFO, *PBPB_INFO;



typedef struct _FCB{
	FSRTL_ADVANCED_FCB_HEADER Header;
	SECTION_OBJECT_POINTERS SectionObjectPointers;
	FAST_MUTEX AdvancedFcbHeaderMutex;
	ERESOURCE Resource;
	ERESOURCE PagingIoResource;
	
	PVCB Vcb;
	
	//FS
	ULONG FirstClusterOfFile;
	
} FCB, *PFCB, DCB, *PDCB;

typedef struct _VCB {
	FSRTL_ADVANCED_FCB_HEADER VolumeFileHeader;
	FAST_MUTEX AdvancedFcbHeaderMutex;

	PFILE_OBJECT VirtualVolumeFile;
	SECTION_OBJECT_POINTERS SectionObjectPointers;

	PVPB Vpb;
	PDEVICE_OBJECT TargetDeviceObject;
	PDEVICE_OBJECT RealDevice;
	
	PDCB RootDcb;
	
	BPB_INFO Bpb;
} VCB, * PVCB;


typedef struct _CCB {
	ULONG dummy;
} CCB, *PCCB;

#endif /* _MEMORY_DATA_H_ */

