#include "fs_common.h"


NTSTATUS Fat32Close(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] Fat32Close in\n");

	FsRtlEnterFileSystem();

	FsRtlExitFileSystem();

	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_UNSUCCESSFUL;
}

