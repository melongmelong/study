SECTIONS {
	/*. = 0xFFFC0000;*/
	. = 0x00000000; /*ok now(not relates to address location)*/
	.dummy : {
		BYTE(0xff);
		. = 0x3fff0;
	} =0xffffffff
	.header.reset : {
		*(.head.reset);
		BYTE(0x00);
		. = 16;
	 } =0x00000000
}
