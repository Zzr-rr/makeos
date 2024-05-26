/* 告诉C编译器，有一个函数在别的文件里 */
void io_hlt(void);
void io_cli(void);
void init_gdtidt(void);
void load_gdtr(int limit, int addr);
void load_idtr(int limit, int addr);

#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

struct BOOTINFO {
    /*
    CYLS	EQU		0x0ff0			; 引导扇区设置
    LEDS	EQU		0x0ff1
    VMODE	EQU		0x0ff2			; 关于颜色的信息
    SCRNX	EQU		0x0ff4			; 分辨率X
    SCRNY	EQU		0x0ff6			; 分辨率Y
    VRAM	EQU		0x0ff8			; 图像缓冲区的起始地址
    */
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
};

void HariMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *) 0x0ff0;
    char s[40];

    init_palette();
    init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
    putfonts8_asc(binfo->vram, binfo->scrnx, 8, 8, COL8_FFFFFF, "Haribote OS.");
    putfonts8_asc(binfo->vram, binfo->scrnx, 31, 31, COL8_000000, "LJY 520.");
    putfonts8_asc(binfo->vram, binfo->scrnx, 30, 30, COL8_FFFFFF, "LJY 520.");

    /*sprintf函数将字符串内容放到s字符串中*/
    sprintf(s, "scrnx = %d", binfo->scrny);
    /*这时候可以通过putfonts函数将存放在s中的字符串输出*/
    putfonts8_asc(binfo->vram, binfo->scrnx, 16, 64, COL8_FFFFFF, s);

    for (;;) {
        io_hlt();
    }
}

