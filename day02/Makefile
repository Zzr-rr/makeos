ipl.bin : ipl.nas Makefile
	..\tools\tolset_h\z_tools\nask.exe ipl.nas ipl.bin ipl.lst
helloos.img : ipl.bin Makefile
	..\tools\tolset_h\z_tools\edimg.exe imgin:..\tools\tolset_h\z_tools\fdimg0at.tek \
	wbinimg src:ipl.bin len:512 from:0 to:0 imgout:helloos.img
run helloos.img:
	F:\Develop\qemu\qemu-system-x86_64.exe helloos.img