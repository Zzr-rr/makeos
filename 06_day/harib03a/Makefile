TOOLPATH = ../../tools/tolset_h/z_tools/
INCPATH  = ../../tools/tolset_h/z_tools/haribote/
QEMU = F:\Develop\qemu\qemu-system-x86_64.exe

MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com

CC1      = $(TOOLPATH)cc1.exe -I$(INCPATH) -Os -Wall -quiet
GAS2NASK = $(TOOLPATH)gas2nask.exe -a
OBJ2BIM  = $(TOOLPATH)obj2bim.exe
BIM2HRB  = $(TOOLPATH)bim2hrb.exe
BIN2OBJ  = $(TOOLPATH)bin2obj.exe
RULEFILE = $(TOOLPATH)haribote/haribote.rul
MAKEFONT = $(TOOLPATH)makefont.exe

COPY     = copy
DEL      = del

LOADER = loader
#默认操作

default :
	$(MAKE) img

#文件生成规则

${LOADER}.bin:
	${NASK} ${LOADER}.nas ${LOADER}.bin

#命令

img :
	$(MAKE) ${SRC}.img

install :
	$(MAKE) img
	$(IMGTOL) w a: haribote.img

run :clean haribote.img
	${QEMU} -drive file=haribote.img,format=raw,if=floppy

clean:
	-$(DEL) ${LOADER}.bin 
	-$(DEL) ${SRC}.sys 
	-$(DEL) ${SRC}.lst
	-$(DEL) bootpack.obj
	-$(DEL) bootpack.bim
	-$(DEL) bootpack.map
	-$(DEL) bootpack.hrb
	-$(DEL) haribote.img
	-$(DEL) haribote.sys
	-$(DEL) asmhead.bin
	-$(DEL) hankaku.bin
	-$(DEL) hankaku.obj
	-$(DEL) /Q *.lst *.gas *.obj
	-$(DEL) graphic.nas
	-$(DEL) dsctbl.nas

asmhead.bin : asmhead.nas Makefile
	$(NASK) asmhead.nas asmhead.bin asmhead.lst

bootpack.gas : bootpack.c Makefile
	$(CC1) -o bootpack.gas bootpack.c

bootpack.nas : bootpack.gas Makefile
	$(GAS2NASK) bootpack.gas bootpack.nas

bootpack.obj : bootpack.nas Makefile
	$(NASK) bootpack.nas bootpack.obj bootpack.lst

naskfunc.obj : naskfunc.nas Makefile
	$(NASK) naskfunc.nas naskfunc.obj naskfunc.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.obj : hankaku.bin Makefile
	$(BIN2OBJ) hankaku.bin hankaku.obj _hankaku

dsctbl.gas : dsctbl.c Makefile
	$(CC1) -o dsctbl.gas dsctbl.c

dsctbl.nas : dsctbl.gas Makefile
	$(GAS2NASK) dsctbl.gas dsctbl.nas

dsctbl.obj : dsctbl.nas Makefile
	$(NASK) dsctbl.nas dsctbl.obj dsctbl.lst

graphic.gas : graphic.c Makefile
	$(CC1) -o graphic.gas graphic.c

graphic.nas : graphic.gas Makefile
	$(GAS2NASK) graphic.gas graphic.nas

graphic.obj : graphic.nas Makefile
	$(NASK) graphic.nas graphic.obj graphic.lst

bootpack.bim : bootpack.obj graphic.obj dsctbl.obj naskfunc.obj hankaku.obj Makefile
	$(OBJ2BIM) @$(RULEFILE) out:bootpack.bim stack:3136k map:bootpack.map \
		bootpack.obj graphic.obj dsctbl.obj naskfunc.obj hankaku.obj



bootpack.hrb : bootpack.bim Makefile
	$(BIM2HRB) bootpack.bim bootpack.hrb 0

haribote.sys : asmhead.bin bootpack.hrb Makefile
	copy /B asmhead.bin+bootpack.hrb haribote.sys

haribote.img : ${LOADER}.bin haribote.sys Makefile
	$(EDIMG)   imgin:${TOOLPATH}fdimg0at.tek \
		wbinimg src:${LOADER}.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:haribote.img