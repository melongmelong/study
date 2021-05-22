PHDRS {
	text PT_LOAD;
}

SECTIONS {
	rom_start = 0xFFFC0000;
	rom_end = 0xFFFFFFFF;
	reset_start = 0xFFFFFFF0;
	reset_end = 0xFFFFFFFF; /*== rom_end*/

	. = rom_start;
	/*. = 0x00000000;*/ /*ok now(not relates to address location)*/
	/*
	.dummy : {
		BYTE(0xff);
		. = 0x3fff0;
	} =0xffffffff
	*/
	.text : {
		*(.text);
	} :text
	.head.start : {
		*(.head.start);
	}
	offset = reset_start - .;
	.dummy : {
		FILL(0xff);
		. = offset;
	}
	. = reset_start;
	offset = reset_end - reset_start + 1;
	.head.reset : {
		FILL(0xff);
		*(.head.reset);
		. = offset;
	 }
	. = rom_end;

	/DISCARD/ : {
		*(.eh_frame);
	}
	
}
