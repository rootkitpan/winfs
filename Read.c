#include "fs_common.h"


NTSTATUS DispatchRead(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] %s %p in\n", __func__, DeviceObject);

	FsRtlEnterFileSystem();

	FsRtlExitFileSystem();

	Irp->IoStatus.Status = STATUS_UNSUCCESSFUL;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_UNSUCCESSFUL;
}