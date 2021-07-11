SRCS=reset.S start.S main.c dummy.S bzImage.c initramfs.c bzImage_tmp.S run.S
OBJS=reset.o start.o main.o dummy.o bzImage.o initramfs.o bzImage_tmp.o run.o
LINKER_SCRIPT=linker_script.ld
IMG_ELF=img.elf
IMG_BIN=img.bin

all: ${OBJS}
	ld -m elf_i386 -T ${LINKER_SCRIPT} -o ${IMG_ELF} ${OBJS}
	objcopy -O binary ${IMG_ELF} ${IMG_BIN}

initramfs.c: initramfs.cpio.xz
	xxd -i $< 1>$@
bzImage.c: bzImage
	xxd -i $< 1>$@

%.o:%.c
	gcc -m32 -fno-pic -fno-builtin -fno-stack-protector -c $<
%.o:%.S
	gcc -m32 -fno-pic -fno-builtin -fno-stack-protector -c $<

clean:
	rm -rf ${IMG_ELF} ${IMG_BIN} ${OBJS} bzImage.c initramfs.c
