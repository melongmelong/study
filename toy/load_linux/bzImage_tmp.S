.section ".main.text", "ax", @progbits
.code32
	movl $0x12345678, %eax;
	movl $0x12345678, %ebx;
	movl $0x12345678, %ecx;
	movl $0x12345678, %edx;
	hlt;
