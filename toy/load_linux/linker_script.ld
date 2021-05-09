SECTIONS {
	. = 0xFFFEFFFF;
	.dummy : {
		BYTE(0xff);
		. = 0xfff0;
	} =0xffffffff

	. = 0xfffffff0;
	.header : {
		*(*);
		. = 14;
		BYTE(0x00);
	 } =0x00000000
}
