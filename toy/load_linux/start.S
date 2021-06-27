.section ".head.start", "ax", @progbits
.code16
.global _start
_start:
	movb $0x34, %al;

	cli;

	//load gdtr. from coreboot ./src/cpu/x86/16bit/entry16.inc
	movw %cs, %ax;
	shlw $4, %ax;
	movw $gdtptr_offset, %bx;
	subw %ax, %bx;
	lgdtl %cs:(%bx);

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

	hlt;
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
