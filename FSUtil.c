#include "fs_common.h"




NTSTATUS DecodeFileObject (
	PFILE_OBJECT FileObject,
	PULONG Type,
	PVCB *Vcb,
	PFCB *Fcb,			// FCB or DCB
	PCCB *Ccb
)
{
	PVOID FsContext = FileObject->FsContext;			// FCB DCB VCB
	PVOID FsContext2 = FileObject->FsContext2;			// CCB
	
	*Type = UNKNOWN_FILE_OBJECT;
	*Vcb = NULL;
	*Fcb = NULL;
	*Ccb = NULL;
	
	if(FsContext == NULL){
		// FsContext not set yet
		return STATUS_SUCCESS;
	}
	
	switch(NodeType(FsContext)){
	case FAT_NTC_VCB:
		if(FsContext2 == NULL){
			*Type = VOLUME_STREAM_FILE;
			*Vcb = FsContext;
			*Fcb = NULL;
			*Ccb = NULL;
		} else {
			*Type = USER_VOLUME;
			*Vcb = FsContext;
			*Fcb = NULL;
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










