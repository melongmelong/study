#include "main.h"

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

#define E820MAX 32              /* number of entries in E820MAP */
struct e820entry {
	u64 addr;               /* start of memory segment */
	u64 size;               /* size of memory segment */
	u32 type;               /* type of memory segment */
	#define E820_RAM        1
	#define E820_RESERVED   2  
	#define E820_ACPI       3       /* usable as RAM once ACPI tables have been read */
	#define E820_NVS        4
};

/* Parameters passed to 32-bit part of Linux
 * This is another view of the structure above.. */
struct linux_params {
	u8 orig_x;		/* 0x00 */
	u8 orig_y;		/* 0x01 */
	u16 ext_mem_k;		/* 0x02 -- EXT_MEM_K sits here */
	u16 orig_video_page;	/* 0x04 */
	u8 orig_video_mode;	/* 0x06 */
	u8 orig_video_cols;	/* 0x07 */
	u16 unused2;		/* 0x08 */
	u16 orig_video_ega_bx;	/* 0x0a */
	u16 unused3;		/* 0x0c */
	u8 orig_video_lines;	/* 0x0e */
	u8 orig_video_isVGA;	/* 0x0f */
	u16 orig_video_points;	/* 0x10 */

	/* VESA graphic mode -- linear frame buffer */
	u16 lfb_width;		/* 0x12 */
	u16 lfb_height;		/* 0x14 */
	u16 lfb_depth;		/* 0x16 */
	u32 lfb_base;		/* 0x18 */
	u32 lfb_size;		/* 0x1c */
	u16 cl_magic;		/* 0x20 */
#define CL_MAGIC_VALUE 0xA33F
	u16 cl_offset;		/* 0x22 */
	u16 lfb_linelength;	/* 0x24 */
	u8 red_size;		/* 0x26 */
	u8 red_pos;		/* 0x27 */
	u8 green_size;		/* 0x28 */
	u8 green_pos;		/* 0x29 */
	u8 blue_size;		/* 0x2a */
	u8 blue_pos;		/* 0x2b */
	u8 rsvd_size;		/* 0x2c */
	u8 rsvd_pos;		/* 0x2d */
	u16 vesapm_seg;		/* 0x2e */
	u16 vesapm_off;		/* 0x30 */
	u16 pages;		/* 0x32 */
	u8 reserved4[12];	/* 0x34 -- 0x3f reserved for future expansion */

	//struct apm_bios_info apm_bios_info;   /* 0x40 */
	u8 apm_bios_info[0x40];
	//struct drive_info_struct drive_info;  /* 0x80 */
	u8 drive_info[0x20];
	//struct sys_desc_table sys_desc_table; /* 0xa0 */
	u8 sys_desc_table[0x140];
	u32 alt_mem_k;		/* 0x1e0 */
	u8 reserved5[4];	/* 0x1e4 */
	u8 e820_map_nr;		/* 0x1e8 */
	u8 reserved6[8];	/* 0x1e9 */
				/* This next variable is to show where
				 * in this struct the Linux setup_hdr
				 * is located. It does not get filled in.
				 * We may someday find it useful to use
				 * its address. */
	u8 setup_hdr;           /* 0x1f1  */
	u16 mount_root_rdonly;	/* 0x1f2 */
	u8 reserved7[4];	/* 0x1f4 */
	u16 ramdisk_flags;	/* 0x1f8 */
#define RAMDISK_IMAGE_START_MASK	0x07FF
#define RAMDISK_PROMPT_FLAG		0x8000
#define RAMDISK_LOAD_FLAG		0x4000
	u8 reserved8[2];	/* 0x1fa */
	u16 orig_root_dev;	/* 0x1fc */
	u8 reserved9[1];	/* 0x1fe */
	u8 aux_device_info;	/* 0x1ff */
	u8 reserved10[2];	/* 0x200 */
	u8 param_block_signature[4];	/* 0x202 */
	u16 param_block_version;	/* 0x206 */
	u8 reserved11[8];	/* 0x208 */
	u8 loader_type;		/* 0x210 */
#define LOADER_TYPE_LOADLIN         1
#define LOADER_TYPE_BOOTSECT_LOADER 2
#define LOADER_TYPE_SYSLINUX        3
#define LOADER_TYPE_ETHERBOOT       4
#define LOADER_TYPE_KERNEL          5
	u8 loader_flags;	/* 0x211 */
	u8 reserved12[2];	/* 0x212 */
	u32 kernel_start;	/* 0x214 */
	u32 initrd_start;	/* 0x218 */
	u32 initrd_size;	/* 0x21c */
	u8 reserved12_5[8];	/* 0x220 */
	u32 cmd_line_ptr;	/* 0x228 */
	u32 initrd_addr_max;	/* 0x22c */
	u32 kernel_alignment;	/* 0x230 */
	u8 relocatable_kernel;	/* 0x234 */
	u8 reserved13[0x2b];		/* 0x235 */
	u32 init_size;          /* 0x260 */
	u8 reserved14[0x6c];		/* 0x264 */
	struct e820entry e820_map[E820MAX];	/* 0x2d0 */
	u8 reserved16[688];	/* 0x550 */
#define COMMAND_LINE_SIZE 256
	/* Command line is copied here by 32-bit i386/kernel/head.S.
	 * So I will follow the boot protocol, rather than putting it
	 * directly here. --ts1 */
	u8 command_line[COMMAND_LINE_SIZE];	/* 0x800 */
	u8 reserved17[1792];	/* 0x900 - 0x1000 */
};

extern char bzImage_img[];
extern unsigned int bzImage_img_len;
extern char initramfs_cpio_xz[];
extern unsigned int initramfs_cpio_xz_len;
extern char *kernel_gdt, *kernel_gdtend;

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

void memset(char *dst, char val, int size)
{
	int i;

	for(i=0; i<size; i++){
		dst[i] = val;
	}
}

int main(void)
{
	struct linux_params *linux_params;
	struct linux_header *linux_header;
	char setup_sects;
	short version;
	char cmdline='\0';

	setup_sects = bzImage_img[0x1f1];
	if(setup_sects == 0){
		setup_sects = 4;
	}

	memset((char*)PARAM_START, 0, 512*(setup_sects+1));
	memcpy((char*)PARAM_START, &bzImage_img[0], 512*(setup_sects+1));

	memcpy((char*)CMDLINE_START, &cmdline, 1);

	memcpy((char*)PROTECTED_MODE_KERNEL_START, &bzImage_img[512*(setup_sects+1)], bzImage_img_len-(512*(setup_sects+1)));

	memcpy((char*)RAMDISK_START, &initramfs_cpio_xz[0], initramfs_cpio_xz_len);
	
	linux_params = (struct linux_params*)PARAM_START;
	linux_header = (struct linux_header*)PARAM_START;

	version = linux_header->protocol_version;

	linux_header->vid_mode = 0xffff;

	linux_header->type_of_loader = 0xff;
	
	linux_header->loadflags = linux_header->loadflags | 0x80 & 0xdf;

	linux_header->ramdisk_image = RAMDISK_START;
	linux_header->ramdisk_size = initramfs_cpio_xz_len;

	linux_header->heap_end_ptr = 0x9800-0x200;
	
	linux_header->cmd_line_ptr = CMDLINE_START;

	linux_params->orig_video_mode = 3;
	linux_params->orig_video_cols = 80;
	linux_params->orig_video_lines = 25;
	linux_params->orig_video_isVGA = 1;
	linux_params->orig_video_points = 16;
	
	linux_params->e820_map_nr = 5;

	linux_params->e820_map[0].addr = 0x00001000;
	linux_params->e820_map[0].size = 0x9EFFF;
	linux_params->e820_map[0].type = E820_RAM;
	linux_params->e820_map[1].addr = 0x000a0000;
	linux_params->e820_map[1].size = 0x5FFFF;
	linux_params->e820_map[1].type = E820_RESERVED;	
	linux_params->e820_map[2].addr = 0x00100000;
	linux_params->e820_map[2].size = 0xBFE80FFF;
	linux_params->e820_map[2].type = E820_RAM;
	linux_params->e820_map[3].addr = 0xff800000;
	linux_params->e820_map[3].size = 0x7FFFFF;
	linux_params->e820_map[3].type = E820_RESERVED;
	linux_params->e820_map[4].addr = 0x100000000;
	linux_params->e820_map[4].size = 0x3FFFFFFF;
	linux_params->e820_map[4].type = E820_RAM;
	
	return 0;
}
