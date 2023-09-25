#include "fs_common.h"




NTSTATUS DecodeFileObject (
	PFILE_OBJECT FileObject,
	PULONG Type,
	PVCB *Vcb,
	PFCB *FcbOrDcb,
	PCCB *Ccb
)
{
	PVOID FsContext = FileObject->FsContext;			// FCB DCB VCB
	PVOID FsContext2 = FileObject->FsContext2;			// CCB
	
	if(FsContext == NULL){
		return STATUS_UNSUCCESSFUL;
	}
	
	switch(NodeType(FsContext)){
	case FAT_NTC_VCB:
		if(FsContext2 == NULL){
			*Type = VOLUME_STREAM_FILE;
			*Vcb = FsContext;
			*FcbOrDcb = NULL;
			*Ccb = NULL;
		} else {
			*Type = USER_VOLUME;
			*Vcb = FsContext;
			*FcbOrDcb = NULL;
			*Ccb = FsContext2;
		}
		break;
		
	case FAT_NTC_DCB:
		break;
		
	case FAT_NTC_FCB:
		break;
		
	default:
		return STATUS_UNSUCCESSFUL;
	}
	
	return STATUS_SUCCESS;
}










