NASK = ..\..\tools\tolset_h\z_tools\nask.exe
EDIMG = ..\..\tools\tolset_h\z_tools\edimg.exe
FDIMG = ..\..\tools\tolset_h\z_tools\fdimg0at.tek
QEMU = F:\Develop\qemu\qemu-system-x86_64.exe
SRC = harib00c

${SRC}.bin : ${SRC}.nas Makefile
	${NASK} ${SRC}.nas ${SRC}.bin ${SRC}.lst
floppy.img : ${SRC}.bin Makefile
	${EDIMG} imgin:${FDIMG} \
	wbinimg src:${SRC}.bin len:512 from:0 to:0 imgout:floppy.img
run :floppy.img
	${QEMU} -drive file=floppy.img,format=raw,if=floppy
