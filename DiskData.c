#include "fs_common.h"

NTSTATUS Fat32CheckBootSector(PFAT32_BOOT_SECTOR BootSector)
{
	if ( 
		((BootSector->BS_jmpBoot[0] != 0xEB) && (BootSector->BS_jmpBoot[2] != 0x90)) ||
		(BootSector->BS_jmpBoot[0] != 0xE9)
	) {
		DbgPrint("[Fat32][error] BootSector->Jump = 0x%02X 0x%02X 0x%02X\n", 
			BootSector->BS_jmpBoot[0],
			BootSector->BS_jmpBoot[1],
			BootSector->BS_jmpBoot[2]);
		
		// for debug, we may comment out return -1
		//return -1;
	}

	if ((BootSector->BPB_BytsPerSec != 512) &&
		(BootSector->BPB_BytsPerSec != 1024) &&
		(BootSector->BPB_BytsPerSec != 2048) &&
		(BootSector->BPB_BytsPerSec != 4096) ) 
	{
		DbgPrint("[Fat32][error] BootSector->BPB_BytsPerSec = %d\n",
			BootSector->BPB_BytsPerSec);
		return -2;
	}

	if ((BootSector->BPB_SecPerClus != 1) &&
		(BootSector->BPB_SecPerClus != 2) &&
		(BootSector->BPB_SecPerClus != 4) &&
		(BootSector->BPB_SecPerClus != 8) &&
		(BootSector->BPB_SecPerClus != 16) &&
		(BootSector->BPB_SecPerClus != 32) &&
		(BootSector->BPB_SecPerClus != 64) &&
		(BootSector->BPB_SecPerClus != 128) ) 
	{
		return -3;
	}

	if (BootSector->BPB_BytsPerSec * BootSector->BPB_SecPerClus > 32 * 1024) {
		return -4;
	}

	if (BootSector->BPB_RsvdSecCnt == 0) {
		return -5;
	}

	if (BootSector->BPB_NumFATs == 0) {
		return -6;
	}

	if (BootSector->BPB_RootEntCnt != 0) {
		// This is not Fat32
		return -7;
	}

	if (BootSector->BPB_TotSec16 != 0){
		return -8;
	}

	if ((BootSector->BPB_Media != 0xF0) &&
		(BootSector->BPB_Media != 0xF8) &&
		(BootSector->BPB_Media != 0xF9) &&
		(BootSector->BPB_Media != 0xFA) &&
		(BootSector->BPB_Media != 0xFB) &&
		(BootSector->BPB_Media != 0xFB) &&
		(BootSector->BPB_Media != 0xFC) &&
		(BootSector->BPB_Media != 0xFD) &&
		(BootSector->BPB_Media != 0xFE) &&
		(BootSector->BPB_Media != 0xFF) ) 
	{
		return -9;
	}

	if (BootSector->BPB_FatSz32 != 0) {
		// Fat32
		return -10;
	}

	if (BootSector->BPB_ExtFlags & 0x80) {
		//
		//  If this is FAT32 (i.e., extended BPB), look for and refuse to mount
		//  mirror-disabled volumes. If we did, we would need to only write to
		//  the FAT# indicated in the ActiveFat field. The only user of this is
		//  the FAT->FAT32 converter after the first pass of protected mode work
		//  (booting into realmode) and NT should absolutely not be attempting
		//  to mount such an in-transition volume.
		//
		return -13;
	}

	return 0;
}



