TOOLPATH = ../../tools/tolset_h/z_tools/
MAKE     = $(TOOLPATH)make.exe -r
NASK     = $(TOOLPATH)nask.exe
EDIMG    = $(TOOLPATH)edimg.exe
IMGTOL   = $(TOOLPATH)imgtol.com
QEMU = F:\Develop\qemu\qemu-system-x86_64.exe
COPY     = copy
DEL      = del
LOADER = loader
SRC = haribote
#默认操作

default :
	$(MAKE) img

#文件生成规则

${LOADER}.bin:
	${NASK} ${LOADER}.nas ${LOADER}.bin

${SRC}.sys : ${SRC}.nas Makefile
	$(NASK) ${SRC}.nas ${SRC}.sys ${SRC}.lst

${SRC}.img : clean ${LOADER}.bin ${SRC}.sys Makefile
	$(EDIMG)   imgin:${TOOLPATH}fdimg0at.tek wbinimg src:${LOADER}.bin len:512 from:0 to:0 copy from:${SRC}.sys to:@: imgout:${SRC}.img


#命令

img :
	$(MAKE) ${SRC}.img

install :
	$(MAKE) img
	$(IMGTOL) w a: haribote.img

run :clean ${SRC}.img
	${QEMU} -drive file=${SRC}.img,format=raw,if=floppy

clean:
	-$(DEL) ${LOADER}.bin 
	-$(DEL) ${SRC}.sys 
	-$(DEL) ${SRC}.lst