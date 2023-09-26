#include "fs_common.h"


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
			DbgPrint("[Fat32] Type of read is User Volume or virtual volume file\n");


		}
	}


	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);


	if (TopLevel) {
		IoSetTopLevelIrp(NULL);
	}

	FsRtlExitFileSystem();

	return STATUS_UNSUCCESSFUL;
}