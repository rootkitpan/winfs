#include "fs_common.h"


NTSTATUS DispatchClose(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] IRP_MJ_CLOSE in\n");

	FsRtlEnterFileSystem();

	FsRtlExitFileSystem();

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	DbgPrint("[Fat32] IRP_MJ_CLOSE out\n");

	return STATUS_UNSUCCESSFUL;
}

