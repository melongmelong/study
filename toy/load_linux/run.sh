#/bin/bash
#qemu-system-x86_64 -m 4g -bios ./img.bin -monitor stdio
qemu-system-x86_64 -m 4g -bios ./img.bin -serial stdio
