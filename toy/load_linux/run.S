#define RUN_START 0x00000100

.section ".head.run", "ax", @progbits
.code32
_to16:
	cli;

	//load 16bit gdt and jmp to use 16bit cs segment
	movl $(RUN_START+gdt16ptr-_to16), %eax;
	lgdtl (%eax);

	ljmp $0x08, $(RUN_START+1f-_to16);
1:
.code16
	movw $0x10, %ax;
	movw %ax, %ds;
	movw %ax, %es;
	movw %ax, %ss;
	movw %ax, %fs;
	movw %ax, %gs;

	movl $(RUN_START+runidt_offset), %eax;
	lidtl (%eax);

	movl %cr0, %eax;
	andl $0x7ffffffe, %eax;
	movl %eax, %cr0;

	//jmp to real mode
	ljmp $0x0000, $(RUN_START+run_offset);

.code16
.global _run //real mode
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

	movw $0x8000, %bx;
	movw $(0x9800-0x200), %cx;

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

	ljmp $0x8020, $0x0000;

	hlt;

.global null16idt
null16idt:
	.word 0
	.long 0
	.word 0
gdt16ptr:
	.word gdt16_end-gdt16-1
	.long RUN_START+gdt16-_to16
gdt16:
	.word 0x0000, 0x0000 //dummy
	.word 0x0000, 0x0000

	.word 0xffff, 0x0000 //flat 64k segment for code 
	.byte 0x00, 0x9b, 0x00, 0x00

	.word 0xffff, 0x0000 //flat 64k segment for data 
	.byte 0x00, 0x93, 0x00, 0x00
gdt16_end:
