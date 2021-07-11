#define RUN_START 0x00000100

.section ".head.run", "ax", @progbits
.code32
_to16:
	cli;

	movl $gdt16ptr, %eax;
	lgdtl (%eax);

	movw $0x10, %ax;
	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	movl $(RUN_START+runidt_offset), %eax;
	lidtl (%eax);

	movw $0x9000, %bx;
	movw $(0x10000-0x200), %cx;

	movl %cr0, %eax;
	andl $0x7ffffffe, %eax;
	movl %eax, %cr0;

	ljmp $0x0000, $(RUN_START+run_offset);

.code16
.global _run
_run:
	xorw %ax, %ax;
	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	sti;

	//run kernel
	cli;

	movw %bx, %ss;
	movw %cx, %sp;

	movw %bx, %ax;
	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	xorw %ax, %ax;
	xorw %bx, %bx;
	xorw %cx, %cx;
	xorw %dx, %dx;
	xorw %bp, %bp;
	xorw %sp, %sp;

	.byte 0xea
	.long 0x00000000
	.word 0x9020	

//	ljmp $0x9020, $0;

	hlt;

.global null16idt
null16idt:
	.word 0
	.long 0
	.word 0
gdt16ptr:
	.word gdt16_end-gdt16-1
	.long gdt16
gdt16:
	.word 0x0000, 0x0000 //dummy
	.word 0x0000, 0x0000

	.word 0xffff, 0x0000 //flat 4g segment for code
	.byte 0x00, 0x9b, 0xcf, 0x00

	.word 0xffff, 0x0000 //flat 4g segment for data 
	.byte 0x00, 0x93, 0x40, 0x00
gdt16_end:
