/* 告诉C编译器，有一个函数在别的文件里 */
#include "bootpack.h"

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