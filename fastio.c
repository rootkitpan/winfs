#include "fs_common.h"


BOOLEAN Fat32FastIoCheckIfPossible(
    PFILE_OBJECT FileObject,
    PLARGE_INTEGER FileOffset,
    ULONG Length,
    BOOLEAN Wait,
    ULONG LockKey,
    BOOLEAN CheckForReadOperation,
    PIO_STATUS_BLOCK IoStatus,
    PDEVICE_OBJECT DeviceObject
)
{
    DbgPrint("[Fat32] Fat32FastIoCheckIfPossible in\n");

    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(FileOffset);
    UNREFERENCED_PARAMETER(Length);
    UNREFERENCED_PARAMETER(Wait);
    UNREFERENCED_PARAMETER(LockKey);
    UNREFERENCED_PARAMETER(CheckForReadOperation);
    UNREFERENCED_PARAMETER(IoStatus);
    UNREFERENCED_PARAMETER(DeviceObject);

    return FALSE;
}

#if 0
BOOLEAN Fat32FastIoRead(
    PFILE_OBJECT FileObject,
    PLARGE_INTEGER FileOffset,
    ULONG Length,
    BOOLEAN Wait,
    ULONG LockKey,
    _Out_ PVOID Buffer,
    _Out_ PIO_STATUS_BLOCK IoStatus,
    PDEVICE_OBJECT DeviceObject
)
{
    DbgPrint("[Fat32] Fat32FastIoRead in\n");

    return FALSE;
}
#endif

