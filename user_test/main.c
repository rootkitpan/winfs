#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "../fat32disk.h"

FAT32_BOOT_SECTOR BootSector;

static void PrintBootSector(PFAT32_BOOT_SECTOR bs)
{
	int i;

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



	//
	//printf("sizeof(FAT32_BOOT_SECTOR) = %d", sizeof(FAT32_BOOT_SECTOR));
	DWORD bytesRead = 0;
	BOOL bRet = FALSE;
	bRet = ReadFile(hVolume, &BootSector, sizeof(FAT32_BOOT_SECTOR), &bytesRead, NULL);
	if( (bRet != TRUE) || (bytesRead != sizeof(FAT32_BOOT_SECTOR)) ){
		printf("[error] ReadFile\n");
		return -1;
	}

	PrintBootSector(&BootSector);





	CloseHandle(hVolume);

	return 0;
}


