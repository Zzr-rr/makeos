; haribote-os
; TAB=4
    ; 设置显示字符的BIOS调用
    ORG     0xc200          ; 程序被装载的地址。

    MOV     AL,0x13         ; VGA 显卡，320 x 280 x 8位彩色。
    MOV     AH,0x00
    INT     0x10

fin:
    HLT
    JMP     fin