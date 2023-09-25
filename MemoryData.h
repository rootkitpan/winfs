#ifndef _MEMORY_DATA_H_
#define _MEMORY_DATA_H_

#include <ntifs.h>

typedef struct _FCB{
	FSRTL_ADVANCED_FCB_HEADER VolumeFileHeader;
	FAST_MUTEX AdvancedFcbHeaderMutex;
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
} VCB, * PVCB;


typedef struct _CCB {
	ULONG dummy;
} CCB, *PCCB;

#endif /* _MEMORY_DATA_H_ */

