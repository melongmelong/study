#define PARAM_START 0x90000
#define KERNEL_GDT_START 0x40000

.section ".head.start", "ax", @progbits
.code16
.global _start
_start:
	cli;

/*
	//load gdtr. from coreboot ./src/cpu/x86/16bit/entry16.inc
	movw %cs, %ax;
	shlw $4, %ax;
	movw $gdtptr_offset, %bx;
	subw %ax, %bx;
	lgdtl %cs:(%bx);
*/
	movl $gdtptr, %eax;
	lgdtl (%eax);

	movl %cr0, %eax;
	andl $0x7ffaffd1, %eax;
	orl $0x60000001,  %eax;
	movl %eax, %cr0;

	//to protected mode. from coreboot ./src/cpu/x86/16bit/entry16.inc
	ljmpl $0x08, $_protected_start;

.code32
_protected_start:
	movw $0x10, %ax;

	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	sti;

	movl $0x10000000, %ebp
	movl $0x10000000, %esp
	call main;

	mov  $KERNEL_GDT_START, %eax
	movl  $0x0000ffff, 16(%eax)             // Set up the 2 new descriptors
	movl  $0x00cf9b00, 20(%eax)
	movl  $0x0000ffff, 24(%eax)
	movl  $0x00cf9300, 28(%eax)
	movb $0x2b, 0(%eax)                     // Set the size
	movl %eax, 2(%eax)                      // Set pointer to new GDT
	lgdt (%eax)                             // Load it

	movw $0x18, %ax;
	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	cli;

	movl $PARAM_START, %esi;

	xorl %ebp, %ebp
	xorl %edi, %edi
	xorl %ebx, %ebx

	ljmpl $0x10, $_running_kernel;

_running_kernel:
	movl PARAM_START+0x214, %eax;
	jmpl *%eax;
//	jmpl *(PARAM_START+0x214);

.global gdtptr
gdtptr:
	.word gdt_end-gdt-1
	.long gdt
gdt:
	.word 0x0000, 0x0000 //dummy
	.word 0x0000, 0x0000

	.word 0xffff, 0x0000 //flat 4g segment for code
	.byte 0x00, 0x9b, 0xcf, 0x00

	.word 0xffff, 0x0000 //flat 4g segment for data 
	.byte 0x00, 0x93, 0xcf, 0x00
gdt_end:
