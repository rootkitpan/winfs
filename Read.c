#include "fs_common.h"

typedef struct _COMPLETE_CONTEXT {
	KEVENT SyncEvent;
}COMPLETE_CONTEXT, *PCOMPLETE_CONTEXT;

#define COMPLETE_CONTEXT_MEMFLAG	('COMP')


NTSTATUS ReadCompletionRoutine(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp,
	PVOID Context
)
{

}



VOID DispatchReadCommon(PIRP Irp) 
{
	PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
	PFILE_OBJECT FileObject = IrpSp->FileObject;
	PVCB Vcb;
	PFCB Fcb;
	PCCB Ccb;
	ULONG Type;

	BOOLEAN NonCachedIo = BooleanFlagOn(Irp->Flags, IRP_NOCACHE);
	BOOLEAN PagingIo = BooleanFlagOn(Irp->Flags, IRP_PAGING_IO);
	LONGLONG StartingByte = IrpSp->Parameters.Read.ByteOffset.QuadPart;
	ULONG ByteCount = IrpSp->Parameters.Read.Length;

	DbgPrint("[Fat32] %s [%d] [%d] [%lld] [%lu]\n", __func__,
		NonCachedIo, PagingIo, StartingByte, ByteCount);

	DecodeFileObject(FileObject, &Type, &Vcb, &Fcb, &Ccb);

	if (Type == VOLUME_STREAM_FILE) {
		DbgPrint("[Fat32] Type of read is virtual volume file\n");

		PCOMPLETE_CONTEXT Context = FsRtlAllocatePoolWithTag(
			NonPagedPool, sizeof(COMPLETE_CONTEXT), COMPLETE_CONTEXT_MEMFLAG);
		KeInitializeEvent(&Context->SyncEvent, NotificationEvent, FALSE);


		IoSetCompletionRoutine(Irp,
			ReadCompletionRoutine, Context,
			TRUE, TRUE, TRUE);

	}

	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
}




NTSTATUS DispatchRead(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	BOOLEAN TopLevel;

	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] %s %p in\n", __func__, DeviceObject);

	FsRtlEnterFileSystem();

	if (IoGetTopLevelIrp() == NULL) {
		IoSetTopLevelIrp(Irp);
		TopLevel = TRUE;
	}
	else {
		TopLevel = FALSE;
	}

	DispatchReadCommon(Irp);

	if (TopLevel) {
		IoSetTopLevelIrp(NULL);
	}

	FsRtlExitFileSystem();

	return STATUS_UNSUCCESSFUL;
}