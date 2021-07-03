 /* The header of Linux/i386 kernel (from coreboot source code)*/

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct linux_header {
	u8 reserved1[0x1f1];    /* 0x000 */
	u8 setup_sects;         /* 0x1f1 */
	u16 root_flags;         /* 0x1f2 */
	u32 syssize;            /* 0x1f4 (2.04+) */
	u8 reserved2[2];        /* 0x1f8 */
	u16 vid_mode;           /* 0x1fa */
	u16 root_dev;           /* 0x1fc */
	u16 boot_sector_magic;  /* 0x1fe */
	/* 2.00+ */
	u8 reserved3[2];        /* 0x200 */
	u8 header_magic[4];     /* 0x202 */
	u16 protocol_version;   /* 0x206 */
	u32 realmode_swtch;     /* 0x208 */
	u16 start_sys;          /* 0x20c */
	u16 kver_addr;          /* 0x20e */
	u8 type_of_loader;      /* 0x210 */
	u8 loadflags;           /* 0x211 */
	u16 setup_move_size;    /* 0x212 */
	u32 code32_start;       /* 0x214 */
	u32 ramdisk_image;      /* 0x218 */
	u32 ramdisk_size;       /* 0x21c */
	u8 reserved4[4];        /* 0x220 */
	/* 2.01+ */
	u16 heap_end_ptr;       /* 0x224 */
	u8 reserved5[2];        /* 0x226 */
	/* 2.02+ */
	u32 cmd_line_ptr;       /* 0x228 */
	/* 2.03+ */
	u32 initrd_addr_max;    /* 0x22c */
	/* 2.05+ */
	u32 kernel_alignment;   /* 0x230 */
	u8 relocatable_kernel;  /* 0x234 */
	u8 min_alignment;       /* 0x235 (2.10+) */
	u8 reserved6[2];        /* 0x236 */
	/* 2.06+ */
	u32 cmdline_size;       /* 0x238 */
	/* 2.07+ */
	u32 hardware_subarch;   /* 0x23c */
	u64 hardware_subarch_data;/* 0x240 */
	/* 2.08+ */
	u32 payload_offset;     /* 0x248 */
	u32 payload_length;     /* 0x24c */
	/* 2.09+ */
	u64 setup_data;         /* 0x250 */
	/* 2.10+ */
	u64 pref_address;       /* 0x258 */
	u32 init_size;          /* 0x260 */
};

extern char bzImage[];
extern unsigned int bzImage_len;
extern char initramfs_cpio_xz[];
extern unsigned int initramfs_cpio_xz_len;

#define REAL_MODE_CODE_START 0x90000
#define CMDLINE_START 0x9F000
#define PROTECTED_MODE_KERNEL_START 0x100000
#define RAMDISK_START 0x40000000
#define DEBUG_START 0xF0000000

void debug(int offset, char *addr, int size)
{
	char *debug_start = (char*)(DEBUG_START + offset);
	int i=0;

	for(i=0; i<size; i++){
		debug_start[i] = addr[i];
	}
}

void memcpy(char *dst, char *src, int size)
{
	int i;

	for(i=0; i<size; i++){
		dst[i] = src[i];
	}
}

int main(void)
{
	struct linux_header *linux_header;
	char setup_sects;
	char cmdline = '\0';

	setup_sects = bzImage[0x1f1];

	memcpy((char*)REAL_MODE_CODE_START, &bzImage[0], (setup_sects+1)*512);
	linux_header = (struct linux_header*)REAL_MODE_CODE_START;

	linux_header->cmd_line_ptr = CMDLINE_START;
	memcpy((char*)CMDLINE_START, &cmdline, 1);

	memcpy((char*)PROTECTED_MODE_KERNEL_START, &bzImage[(setup_sects+1)*512], bzImage_len-((setup_sects+1)*512));
	
	linux_header->ramdisk_image = RAMDISK_START;
	linux_header->ramdisk_size = initramfs_cpio_xz_len;
	memcpy((char*)RAMDISK_START, &initramfs_cpio_xz[0], initramfs_cpio_xz_len);

	return 0;
}
