#include "fs_common.h"

NTSTATUS PerformDeviceIoControl(
	ULONG IoControlCode,
	PDEVICE_OBJECT Device,
	PVOID InputBuffer, ULONG InputBufferLength,
	PVOID OutputBuffer, ULONG OutputBufferLength,
	BOOLEAN InternalDeviceIoControl
)
{
	NTSTATUS Status;
	PIRP Irp;
	KEVENT Event;
	IO_STATUS_BLOCK LocalIosb;
	PIO_STATUS_BLOCK IosbToUse = &LocalIosb;

	IosbToUse->Status = 0;
	IosbToUse->Information = 0;

	KeInitializeEvent(&Event, NotificationEvent, FALSE);

	Irp = IoBuildDeviceIoControlRequest(IoControlCode,
		Device,
		InputBuffer, InputBufferLength,
		OutputBuffer, OutputBufferLength,
		InternalDeviceIoControl,
		&Event,
		IosbToUse);
	if (Irp == NULL) {
		DbgPrint("[Fat32] IoBuildDeviceIoControlRequest failed\n");
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	Status = IoCallDriver(Device, Irp);

	if (Status == STATUS_PENDING) {

		KeWaitForSingleObject(&Event,
			Executive,
			KernelMode,
			FALSE,
			NULL);

		Status = IosbToUse->Status;
	}
	else if (Status == STATUS_SUCCESS) {
		
	}
	else {
		DbgPrint("[Fat32] IoCallDriver failed 0x%08x\n", Status);
	}

	return Status;
}
