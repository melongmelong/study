SRCS=reset.S start.S #main.c ... if .c file exists, not work correctly (why?)
OBJS=reset.o start.o #main.o
LINKER_SCRIPT=linker_script.ld
IMG_ELF=img.elf
IMG_BIN=img.bin

all: ${OBJS}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o ${IMG_ELF} ${OBJS}
	objcopy -O binary ${IMG_ELF} ${IMG_BIN}

${OBJS}:${SRCS}
	gcc -c $(SRCS) -m32

clean:
	rm -rf ${IMG_ELF} ${IMG_BIN} ${OBJS}
