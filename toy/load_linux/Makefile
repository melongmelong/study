SRCS=reset.S start.S main.c dummy.S 
OBJS=reset.o start.o main.o dummy.o
LINKER_SCRIPT=linker_script.ld
IMG_ELF=img.elf
IMG_BIN=img.bin

all: ${OBJS}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o ${IMG_ELF} ${OBJS}
	objcopy -O binary ${IMG_ELF} ${IMG_BIN}

%.o:%.c
	gcc -m32 -fno-pic -c $<
%.o:%.S
	gcc -m32 -fno-pic -c $<

clean:
	rm -rf ${IMG_ELF} ${IMG_BIN} ${OBJS}
