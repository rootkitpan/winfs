#include "fs_common.h"

// https://learn.microsoft.com/en-us/windows-hardware/drivers/ifs/irp-mj-cleanup
// handle reached 0

NTSTATUS DispatchCleanup(
	PDEVICE_OBJECT DeviceObject,
	PIRP Irp)
{
	BOOLEAN TopLevel;
	
	UNREFERENCED_PARAMETER(DeviceObject);

	DbgPrint("[Fat32] %s %p in\n", __func__, DeviceObject);

	if (DeviceObject == gCDO) {
		DbgPrint("[Fat32] %s Our CDO\n", __func__);

		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = 0;

		IoCompleteRequest(Irp, IO_DISK_INCREMENT);

		DbgPrint("[Fat32] %s out\n", __func__);

		return STATUS_SUCCESS;
	}

	FsRtlEnterFileSystem();

	if ( IoGetTopLevelIrp() == NULL ) {
		IoSetTopLevelIrp( Irp );
		TopLevel = TRUE;
	} else {
		TopLevel = FALSE;
	}
	
	
	
	
	
	
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	
	if (TopLevel) {
		IoSetTopLevelIrp( NULL );
	}
	
	FsRtlExitFileSystem();

	return STATUS_SUCCESS;
}
