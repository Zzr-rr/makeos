NASK = ..\tools\tolset_h\z_tools\nask.exe
EDIMG = ..\tools\tolset_h\z_tools\edimg.exe
FDIMG = ..\tools\tolset_h\z_tools\fdimg0at.tek
QEMU = F:\Develop\qemu\qemu-system-x86_64.exe

harib00a.bin : harib00a.nas Makefile
	${NASK} harib00a.nas harib00a.bin harib00a.lst
floppy.img : harib00a.bin Makefile
	${EDIMG} imgin:${FDIMG} \
	wbinimg src:harib00a.bin len:512 from:0 to:0 imgout:floppy.img
run :floppy.img
	${QEMU} -drive file=floppy.img,format=raw,if=floppy
