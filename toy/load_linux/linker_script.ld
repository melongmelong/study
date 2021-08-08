PHDRS {
	text PT_LOAD;
}

SECTIONS {
	rom_start = 0xFF7FFFFF;
	rom_end = 0xFFFFFFFF;
	reset_start = 0xFFFFFFF0;
	reset_end = 0xFFFFFFFF; 
	prog_start = 0xFFFFF000;
	prog_end = 0xFFFFFFF0; 

	. = rom_start;
	kernel_start = rom_start;
	.kernel : {
		*(.data);
	} : text
	kernel_end = .;

	offset = prog_start - kernel_end;
	.dummy1 : {
		FILL(0xff);
		. = offset;
	}

	. = prog_start;
	.text : {
		*(.text);
	}
	.head.start : {
		*(.head.start);
	}

	offset = reset_start - .;
	.dummy2 : {
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
