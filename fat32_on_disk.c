#include "fs_common.h"

LONG FatIsBootSectorFat(PFAT32_BOOT_SECTOR BootSector)
{
	if ( ((BootSector->Jump[0] != 0xEB) && (BootSector->Jump[2] != 0x90)) ||
		(BootSector->Jump[0] != 0xE9) 
	) {
		DbgPrint("[Fat32] BootSector->Jump = 0x%02X 0x%02X 0x%02X\n", 
			BootSector->Jump[0],
			BootSector->Jump[1],
			BootSector->Jump[2]);
		
		// for debug, we may comment out return -1
		//return -1;
	}

	if ((BootSector->BytesPerSector != 512) &&
		(BootSector->BytesPerSector != 1024) &&
		(BootSector->BytesPerSector != 2048) &&
		(BootSector->BytesPerSector != 4096)
	) {
		DbgPrint("[Fat32] BootSector->BytesPerSector = %d\n", BootSector->BytesPerSector);
		return -2;
	}

	if ((BootSector->SectorsPerCluster != 1) &&
		(BootSector->SectorsPerCluster != 2) &&
		(BootSector->SectorsPerCluster != 4) &&
		(BootSector->SectorsPerCluster != 8) &&
		(BootSector->SectorsPerCluster != 16) &&
		(BootSector->SectorsPerCluster != 32) &&
		(BootSector->SectorsPerCluster != 64) &&
		(BootSector->SectorsPerCluster != 128)
		) {
		return -3;
	}

	if (BootSector->BytesPerSector * BootSector->SectorsPerCluster > 32 * 1024) {
		return -4;
	}

	if (BootSector->ReservedSectors == 0) {
		return -5;
	}

	if (BootSector->Fats == 0) {
		return -6;
	}

	if (BootSector->RootEntries != 0) {
		// This is not Fat32
		return -7;
	}

	if (BootSector->Sectors != 0){
		return -8;
	}

	if ((BootSector->Media != 0xF0) &&
		(BootSector->Media != 0xF8) &&
		(BootSector->Media != 0xF9) &&
		(BootSector->Media != 0xFA) &&
		(BootSector->Media != 0xFB) &&
		(BootSector->Media != 0xFB) &&
		(BootSector->Media != 0xFC) &&
		(BootSector->Media != 0xFD) &&
		(BootSector->Media != 0xFE) &&
		(BootSector->Media != 0xFF)
		) {
		return -9;
	}

	if (BootSector->SectorsPerFat != 0) {
		// Fat32
		return -10;
	}

	if (BootSector->LargeSectors == 0) {
		// Fat32
		return -11;
	}

	if (BootSector->LargeSectorsPerFat == 0) {
		// Fat32
		return -12;
	}

	if (BootSector->ExtendedFlags & 0x80) {
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

	if (BootSector->FsVersion != 0) {
		return -14;
	}

	return 0;
}

