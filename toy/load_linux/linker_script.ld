PHDRS {
	text PT_LOAD;
}

SECTIONS {
	rom_start = 0xFFFC0000;
	rom_end = 0xFFFFFFFF;
	reset_start = 0xFFFFFFF0;
	reset_end = 0xFFFFFFFF; /*== rom_end*/
	prog_start = 0xFFFF0000;
	prog_end = 0xFFFFFFF0; /*== reset_start*/

	. = rom_start;
	offset = prog_start - rom_start;
	.dummy1 : {
		*(.dummy); /*for dummy data*/
		FILL(0xff);
		. = offset;
	}
	. = prog_start;
	.text : {
		*(.text);
	} :text
	.head.start : {
		*(.head.start);
	}
	offset = reset_start - .;
	.dummy2 : {
		*(.dummy); /*for dummy data*/
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
