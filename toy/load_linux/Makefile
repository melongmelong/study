SRCS=reset.S start.S main.c 
OBJS=reset.o start.o main.o
LINKER_SCRIPT=linker_script.ld
IMG_ELF=img.elf
IMG_BIN=img.bin

all: ${OBJS}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o ${IMG_ELF} ${OBJS}
	objcopy -O binary ${IMG_ELF} ${IMG_BIN}

${OBJS}:${SRCS}
	gcc -m32 -fno-pic -c $(SRCS)

clean:
	rm -rf ${IMG_ELF} ${IMG_BIN} ${OBJS}
