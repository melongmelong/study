.section ".head.reset", "ax", %progbits
.code16

movb $0x12, %cl;
#.byte 0xe9
#.int _start - (. + 2); #from coreboot reset16.inc...
jmp _start;
