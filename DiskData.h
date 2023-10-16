#ifndef _DISK_DATA_H_
#define _DISK_DATA_H_


/*
	Reserved Region
		Boot Sector

	FAT Region

	File and Directory Region
		Directory Entry
*/



#pragma pack(1)
typedef struct _FAT32_BOOT_SECTOR {
	UCHAR	BS_jmpBoot[3];				/* 0 */
	UCHAR	BS_OEMName[8];				/* 3 */
	USHORT	BPB_BytsPerSec;				/* 11 count of bytes per sector */
	UCHAR	BPB_SecPerClus;				/* 13 number of sectors per cluster */
	USHORT	BPB_RsvdSecCnt;				/* 14 number of reserved sectors */
	UCHAR	BPB_NumFATs;				/* 16 count of FATs */
	USHORT	BPB_RootEntCnt;				/* 17 */
	USHORT	BPB_TotSec16;				/* 19 */
	UCHAR	BPB_Media;					/* 21 */
	USHORT	BPB_FATSz16;				/* 22 */
	USHORT	BPB_SecPerTrk;				/* 24 */
	USHORT	BPB_NumHeads;				/* 26 */
	ULONG32	BPB_HiddSec;				/* 28 */
	ULONG32	BPB_TotSec32;				/* 32 total count of sectors */
	ULONG32	BPB_FatSz32;				/* 36 count of sectors for one FAT */
	USHORT	BPB_ExtFlags;				/* 40 */
	USHORT	BPB_FSVer;					/* 42 */
	ULONG32	BPB_RootClus;				/* 44 root directory cluster */
	USHORT	BPB_FSInfo;					/* 48 */
	USHORT	BPB_BkBootSec;				/* 50 */
	UCHAR	BPB_Reserved[12];			/* 52 */
	UCHAR	BS_DrvNum;					/* 64 */
	UCHAR	BS_Reserved1;				/* 65 */
	UCHAR	BS_BootSig;					/* 66 */
	ULONG32	BS_VolID;					/* 67 */
	UCHAR	BS_VolLab[11];				/* 71 */
	UCHAR	BS_FilSysType[8];			/* 82 */
	UCHAR	Reserved[420];				/* 90 */
	UCHAR	Signature[2];				/* 510 */
} FAT32_BOOT_SECTOR, *PFAT32_BOOT_SECTOR;
#pragma pack()



#define FAT32_FSI_LEADSIG		(0x41615252)
#define FAT32_FSI_STRUCSIG		(0x61417272)
#define FAT32_FSI_TRAILSIG		(0xAA550000)

typedef struct _FAT32_FSINFO_SECTOR {
	ULONG32	FSI_LeadSig;				/* 0 */
	UCHAR	FSI_Reserved1[480];			/* 4 */
	ULONG32	FSI_StrucSig;				/* 484 */
	ULONG32	FSI_Free_Count;				/* 488 */
	ULONG32	FSI_Nxt_Free;				/* 492 */
	UCHAR	FSI_Reserved2[12];			/* 496 */
	ULONG32	FSI_TrailSig;				/* 508 */
} FAT32_FSINFO_SECTOR, * PFAT32_FSINFO_SECTOR;


#pragma pack(1)
typedef struct _FAT32_DIRENTRY {
	CHAR	DIR_Name[11];				/* 0 */
	UCHAR	DIR_Attr;					/* 11 */
	UCHAR	DIR_NTRes;					/* 12 */
	UCHAR	DIR_CrtTimeTenth;			/* 13 */
	USHORT	DIR_CrtTime;				/* 14 */
	USHORT	DIR_CrtDate;				/* 16 */
	USHORT	DIR_LstAccDate;				/* 18 */
	USHORT	DIR_FstClusHI;				/* 20 */
	USHORT	DIR_WrtTime;				/* 22 */
	USHORT	DIR_WrtDate;				/* 24 */
	USHORT	DIR_FstClusLO;				/* 26 */
	ULONG32	DIR_FileSize;				/* 28 */
} FAT32_DIRENTRY, *PFAT32_DIRENTRY;
#pragma pack()




// FAT Entry / Cluster
#define FAT32_FAT_ENTRY_MASK			( (ULONG32)0x0FFFFFFF )
#define FAT32_FAT_ENTRY_FREE			( (ULONG32)0x00000000 )
#define FAT32_FAT_ENTRY_RESERVED		( (ULONG32)0x0FFFFFF0 )
#define FAT32_FAT_ENTRY_BAD				( (ULONG32)0x0FFFFFF7 )
#define FAT32_FAT_ENTRY_LAST			( (ULONG32)0x0FFFFFFF )

#define FAT32_CLUSTER_FREE				(0)
#define FAT32_CLUSTER_NEXT				(1)
#define FAT32_CLUSTER_RESERVED			(2)
#define FAT32_CLUSTER_BAD				(3)
#define FAT32_CLUSTER_LAST				(4)
#define FAT32_CLUSTER_UNKNOWN			(5)



NTSTATUS Fat32CheckBootSector(PFAT32_BOOT_SECTOR BootSector);
NTSTATUS Fat32CheckClusterType(ULONG32 FatEntry, ULONG32 *ClusterType);


#endif /* _DISK_DATA_H_ */


