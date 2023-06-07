

/*
	Reserved Region

	FAT Region

	File and Directory Region


*/

#pragma pack(1)
typedef struct _FAT32_BOOT_SECTOR {
	UCHAR	BS_jmpBoot[3];				/* 0 */
	UCHAR	BS_OEMName[8];				/* 3 */
	USHORT	BPB_BytsPerSec;				/* 11 */
	UCHAR	BPB_SecPerClus;				/* 13 */
	USHORT	BPB_RsvdSecCnt;				/* 14 */
	UCHAR	BPB_NumFATs;				/* 16 */
	USHORT	BPB_RootEntCnt;				/* 17 */
	USHORT	BPB_TotSec16;				/* 19 */
	UCHAR	BPB_Media;					/* 21 */
	USHORT	BPB_FATSz16;				/* 22 */
	USHORT	BPB_SecPerTrk;				/* 24 */
	USHORT	BPB_NumHeads;				/* 26 */
	ULONG	BPB_HiddSec;				/* 28 */
	ULONG	BPB_TotSec32;				/* 32 */
	ULONG	BPB_FatSz32;				/* 36 */
	USHORT	BPB_ExtFlags;				/* 40 */
	USHORT	BPB_FSVer;					/* 42 */
	ULONG	BPB_RootClus;				/* 44 */
	USHORT	BPB_FSInfo;					/* 48 */
	USHORT	BPB_BkBootSec;				/* 50 */
	UCHAR	BPB_Reserved[12];			/* 52 */
	UCHAR	BS_DrvNum;					/* 64 */
	UCHAR	BS_Reserved1;				/* 65 */
	UCHAR	BS_BootSig;					/* 66 */
	ULONG	BS_VolID;					/* 67 */
	UCHAR	BS_VolLab[11];				/* 71 */
	UCHAR	BS_FilSysType[8];			/* 82 */
	UCHAR	Reserved[420];				/* 90 */
	UCHAR	Signature[2];				/* 510 */
}FAT32_BOOT_SECTOR, *PFAT32_BOOT_SECTOR;
#pragma pack()



