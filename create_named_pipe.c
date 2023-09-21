#include "fs_common.h"


NTSTATUS DispatchCommon(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	PIO_STACK_LOCATION IrpSp = NULL;

	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] %s in\n", __func__);

	FsRtlEnterFileSystem();

	IrpSp = IoGetCurrentIrpStackLocation(Irp);
	DbgPrint("[Fat32] Fat32Common Major = %d, Minor = %d\n", 
		IrpSp->MajorFunction, IrpSp->MinorFunction);

	FsRtlExitFileSystem();

	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_UNSUCCESSFUL;
}