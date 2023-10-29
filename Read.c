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
	NTSTATUS Status;
	ULONG_PTR Information;
	PCOMPLETE_CONTEXT Context2;
	
	DbgPrint("[Fat32] %s in\n", __func__);
	UNREFERENCED_PARAMETER( DeviceObject );
	
	Status = Irp->IoStatus.Status;
	Information = Irp->IoStatus.Information;
	DbgPrint("[Fat32] Status = 0x%08X, Information = %llu\n", Status, Information);
	
	Context2 = (PCOMPLETE_CONTEXT)Context;
	KeSetEvent( &Context2->SyncEvent, 0, FALSE );
	
	return STATUS_MORE_PROCESSING_REQUIRED;
}



NTSTATUS DispatchReadCommon(PIRP Irp) 
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
	NTSTATUS Status;

	DbgPrint("[Fat32][Read] %s NonCachedIo=%d  PagingIo=%d StartingByte=%lld ByteCount=%lu \n", __func__,
		NonCachedIo, PagingIo, StartingByte, ByteCount);

	DecodeFileObject(FileObject, &Type, &Vcb, &Fcb, &Ccb);

	if (Type == VOLUME_STREAM_FILE) {
		PIO_STACK_LOCATION NextIrpSp;
		PCOMPLETE_CONTEXT Context;
		
		DbgPrint("[Fat32][Read] Type of read is virtual volume file\n");

		Context = FsRtlAllocatePoolWithTag( NonPagedPool, sizeof(COMPLETE_CONTEXT), COMPLETE_CONTEXT_MEMFLAG);
		KeInitializeEvent(&Context->SyncEvent, NotificationEvent, FALSE);


		IoSetCompletionRoutine(Irp,
			ReadCompletionRoutine, Context,
			TRUE, TRUE, TRUE);
		
		NextIrpSp = IoGetNextIrpStackLocation(Irp);
		//DbgPrint("[Fat32] NextIrpSp->MajorFunction = %d\n", NextIrpSp->MajorFunction);
		NextIrpSp->MajorFunction = IRP_MJ_READ;
		//DbgPrint("[Fat32] Length = %d\n", NextIrpSp->Parameters.Read.Length);
		NextIrpSp->Parameters.Read.Length = ByteCount;
		//DbgPrint("[Fat32] ByteOffset = %lld\n", NextIrpSp->Parameters.Read.ByteOffset.QuadPart);
		NextIrpSp->Parameters.Read.ByteOffset.QuadPart = StartingByte;
		
#if 0
		if (FlagOn( IrpContext->Flags, IRP_CONTEXT_FLAG_WRITE_THROUGH )) {

		SetFlag( IrpSp->Flags, SL_WRITE_THROUGH );
		}

		//
		//  If this I/O requires override verify, bypass the verify logic.
		//

		if (FlagOn( IrpContext->Flags, IRP_CONTEXT_FLAG_OVERRIDE_VERIFY )) {

		SetFlag( IrpSp->Flags, SL_OVERRIDE_VERIFY_VOLUME );
		}
#endif
		
		Status = IoCallDriver(Vcb->TargetDeviceObject, Irp);
		//DbgPrint("[Fat32] IoCallDriver Status = 0x%08X\n", Status);
		// STATUS_PENDING = 0x00000103
		
		KeWaitForSingleObject(
			&Context->SyncEvent,
			Executive, KernelMode, FALSE, NULL
		);
		KeClearEvent(&Context->SyncEvent);
		
		if (Irp->IoStatus.Status == STATUS_SUCCESS) {
			//FileObject->CurrentByteOffset.QuadPart = StartingByte + Irp->IoStatus.Information;
		}
		
		IoCompleteRequest( Irp, IO_DISK_INCREMENT );

		return Irp->IoStatus.Status;
		
	} else {
		DbgPrint("[Fat32][Read] unknown Type of read\n");
		Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_DISK_INCREMENT);

		return Irp->IoStatus.Status;
	}

}




NTSTATUS DispatchRead(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	BOOLEAN TopLevel;
	NTSTATUS Status;

	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32][Read] IRP_MJ_READ in\n");

	FsRtlEnterFileSystem();

	if (IoGetTopLevelIrp() == NULL) {
		IoSetTopLevelIrp(Irp);
		TopLevel = TRUE;
	}
	else {
		TopLevel = FALSE;
	}

	Status = DispatchReadCommon(Irp);

	if (TopLevel) {
		IoSetTopLevelIrp(NULL);
	}

	FsRtlExitFileSystem();

	DbgPrint("[Fat32][Read] IRP_MJ_READ out\n");

	return Status;
}