.section ".head.reset", "ax", %progbits
.code16

movb $0x12, %al;
hlt;
