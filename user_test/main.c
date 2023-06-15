#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "../fat32disk.h"

FAT32_BOOT_SECTOR BootSector;
FAT32_BOOT_SECTOR BackupBootSector;
FAT32_FSINFO_SECTOR FSInfoSector;

static void PrintBootSector(PFAT32_BOOT_SECTOR bs)
{
	int i;

	printf("sizeof(FAT32_BOOT_SECTOR) = %llu\n", sizeof(FAT32_BOOT_SECTOR));

	printf("BS_jmpBoot: 0x%02X 0x%02X 0x%02X\n", bs->BS_jmpBoot[0], bs->BS_jmpBoot[1], bs->BS_jmpBoot[2]);
	printf("BS_OEMName: ");
	for (i = 0; i < 8; i++) {
		printf("%c", bs->BS_OEMName[i]);
	}
	printf("\n");
	printf("BPB_BytsPerSec: %u\n", bs->BPB_BytsPerSec);
	printf("BPB_SecPerClus: %u\n", bs->BPB_SecPerClus);
	printf("BPB_RsvdSecCnt: %u\n", bs->BPB_RsvdSecCnt);
	printf("BPB_NumFATs: %u\n", bs->BPB_NumFATs);
	printf("BPB_RootEntCnt: %u\n", bs->BPB_RootEntCnt);
	printf("BPB_TotSec16: %u\n", bs->BPB_TotSec16);
	printf("BPB_Media: 0x%02X\n", bs->BPB_Media);
	printf("BPB_FATSz16: %u\n", bs->BPB_FATSz16);
	printf("BPB_SecPerTrk: %u\n", bs->BPB_SecPerTrk);
	printf("BPB_NumHeads: %u\n", bs->BPB_NumHeads);
	printf("BPB_HiddSec: %u\n", bs->BPB_HiddSec);
	printf("BPB_TotSec32: %u\n", bs->BPB_TotSec32);
	printf("BPB_FatSz32: %u\n", bs->BPB_FatSz32);
	printf("BPB_ExtFlags: 0x%04X\n", bs->BPB_ExtFlags);
	printf("BPB_FSVer: 0x%04X\n", bs->BPB_FSVer);
	printf("BPB_RootClus: %u\n", bs->BPB_RootClus);
	printf("BPB_FSInfo: %u\n", bs->BPB_FSInfo);
	printf("BPB_BkBootSec: %u\n", bs->BPB_BkBootSec);
	printf("BPB_Reserved: ");
	for (i = 0; i < 12; i++) {
		printf("0x%02X ", bs->BPB_Reserved[i]);
	}
	printf("\n");
	printf("BS_DrvNum: 0x%02X\n", bs->BS_DrvNum);
	printf("BS_Reserved1: 0x%02X\n", bs->BS_Reserved1);
	printf("BS_BootSig: 0x%02X\n", bs->BS_BootSig);
	printf("BS_VolID: 0x%08X\n", bs->BS_VolID);
	printf("BS_VolLab: ");
	for (i = 0; i < 11; i++) {
		printf("%c", bs->BS_VolLab[i]);
	}
	printf("\n");
	printf("BS_FilSysType: ");
	for (i = 0; i < 8; i++) {
		printf("%c", bs->BS_FilSysType[i]);
	}
	printf("\n");

	printf("Signature: 0x%02X 0x%02X\n", bs->Signature[0], bs->Signature[1]);

}


static void PrintFSInfoSector(PFAT32_FSINFO_SECTOR fsi)
{
	printf("sizeof(FAT32_FSINFO_SECTOR) = %llu\n", sizeof(FAT32_FSINFO_SECTOR));

	printf("FSI_LeadSig = 0x%08X\n", fsi->FSI_LeadSig);
	printf("FSI_StrucSig = 0x%08X\n", fsi->FSI_StrucSig);
	printf("FSI_Free_Count = 0x%08X(%d)\n", fsi->FSI_Free_Count, fsi->FSI_Free_Count);
	printf("FSI_Free_Count = 0x%08X(%d)\n", fsi->FSI_Nxt_Free, fsi->FSI_Nxt_Free);
	printf("FSI_StrucSig = 0x%08X\n", fsi->FSI_TrailSig);
}

int _tmain(void)
{
	HANDLE hVolume;
	
	hVolume = CreateFile(
		_T("\\\\.\\E:"),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hVolume == INVALID_HANDLE_VALUE) {
		printf("[error] CreateFile\n");
		return -1;
	}


	//Boot Sector
	DWORD bytesRead = 0;
	BOOL bRet = FALSE;
	bRet = ReadFile(hVolume, &BootSector, sizeof(FAT32_BOOT_SECTOR), &bytesRead, NULL);
	if( (bRet != TRUE) || (bytesRead != sizeof(FAT32_BOOT_SECTOR)) ){
		printf("[error] ReadFile\n");
		return -1;
	}

	//PrintBootSector(&BootSector);		printf("\n\n\n\n");



	//Backup Boot Sector
	int BackupBootSector = BootSector.BPB_BkBootSec;
	int SectorSize = BootSector.BPB_BytsPerSec;
	LARGE_INTEGER location;
	location.QuadPart = BackupBootSector * SectorSize;
	if (SetFilePointerEx(hVolume, location, NULL, FILE_BEGIN) == 0) {
		printf("[error] SetFilePointerEx\n");
		return -1;
	}
	bRet = ReadFile(hVolume, &BootSector, sizeof(FAT32_BOOT_SECTOR), &bytesRead, NULL);
	if ((bRet != TRUE) || (bytesRead != sizeof(FAT32_BOOT_SECTOR))) {
		printf("[error] ReadFile boot sector bk\n");
		return -1;
	}
	//PrintBootSector(&BootSector);		printf("\n\n\n\n");





	int FsinfoSector = BootSector.BPB_FSInfo;
	location.QuadPart = FsinfoSector * SectorSize;
	if (SetFilePointerEx(hVolume, location, NULL, FILE_BEGIN) == 0) {
		printf("[error] SetFilePointerEx fs info\n");
		return -1;
	}
	bRet = ReadFile(hVolume, &FSInfoSector, sizeof(FAT32_FSINFO_SECTOR), &bytesRead, NULL);
	if ((bRet != TRUE) || (bytesRead != sizeof(FAT32_FSINFO_SECTOR))) {
		printf("[error] ReadFile FSINFO sector\n");
		return -1;
	}
	PrintFSInfoSector(&FSInfoSector);






	CloseHandle(hVolume);

	return 0;
}


