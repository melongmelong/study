#ifndef _MAIN_H_
#define _MAIN_H_

#define PARAM_START 0x80000
#define STACK_HEAP_START PARAM_START+0x08000
#define CMDLINE_START PARAM_START+0x10000
#define PROTECTED_MODE_KERNEL_START 0x100000
#define RAMDISK_START 0x40000000

#define DEBUG_START 0xA0000000

#endif
