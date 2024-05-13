; hello-os
; TAB=4

		ORG		0x7c00			; 指明程序装载地址

; 标准FAT12格式软盘专用的代码 Stand FAT12 format floppy code

		JMP		entry
		DB		0x90
		DB		"HELLOIPL"		; 启动扇区名称（8字节）
		DW		512				; 每个扇区（sector）大小（必须512字节）
		DB		1				; 簇（cluster）大小（必须为1个扇区）
		DW		1				; FAT（File Allocation Table）起始位置（一般为第一个扇区）
		DB		2				; FAT个数（必须为2）
		DW		224				; 根目录大小（一般为224项）
		DW		2880			; 该磁盘大小（必须为2880扇区1440*1024/512）
		DB		0xf0			; 磁盘类型（必须为0xf0）
		DW		9				; FAT的长度（必??9扇区）
		DW		18				; 一个磁道（track）有几个扇区（必须为18）
		DW		2				; 磁头数（必??2）
		DD		0				; 不使用分区，必须是0
		DD		2880			; 重写一次磁盘大小
		DB		0,0,0x29		; 意义不明（固定）
		DD		0xffffffff		; （可能是）卷标号码
		DB		"HELLO-OS   "	; 磁盘的名称（必须为11字节，不足填空格）
		DB		"FAT12   "		; 磁盘格式名称（必须为8字节，不足填空格）
		RESB	18				; 先空出18字节

; 程序主体

        entry:
            MOV AX,0 ; 初始化寄存器, AX=0 
            MOV SS,AX ; 对SS进行赋值，但并不会使得AX寄存器中的值为空 （PS：COPY可能更能表达其中的含义）
            MOV SP,0x7c00 ; SP：Stack Pointer, 栈指针寄存器。
            MOV DS,AX
            MOV ES,AX;关于ES寄存器，请见3.1、3.2节内容以及3.3节中的图
            MOV SI,msg;由于在这里msg的地址是0x7c74，所以这个指令就是把0x7c74代入到SI寄存器中去。
        putloop:
            MOV AL,[SI]
            ADD SI,1 ; 给SI加1
            CMP AL,0
            JE fin
            ;H、L是寄存器高低位，高位0x0e为当前光标处显示字符功能，低位为字符内容(这里通过把数组每个元素赋值给加法寄存器低位)
            MOV AH,0x0e ; 显示一个文字
            MOV BX,15 ; 指定字符颜色
            INT 0x10 ; 调用显卡BIOS
            JMP putloop
        fin:
            HLT ; 让CPU停止， 等待指令
            ;然而笔者讨厌让CPU毫无意义地空转。 如果没有HLT指令， CPU就会不停地全力去
            ;执行JMP指令， 这会使CPU的负荷达到100%， 非常费电。 这多浪费呀。 我们仅仅加
            ;上一个HLT指令， 就能让CPU基本处于睡眠状态， 可以省很多电
            JMP fin ; 无限循环
        ;按照ASCII码表，这个msg明显就是"\n\nhello, world\n\0"嘛，'\0'是字符串结束符 (NUL)，'\0a'是换行符'\n'(LF)
        msg:
            DB 0x0a, 0x0a ; 换行2次
            DB "hello, world"
            DB 0x0a ; 换行
            DB 0
