.section ".head.start", "ax", %progbits
.code16
.global _start
_start:
	movb $0x34, %al;
	call main;
	movb $0x34, %bl;
	hlt;
