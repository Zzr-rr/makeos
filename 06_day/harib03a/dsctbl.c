/*告诉C编译器，有一个函数在别的文件里*/
void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

/**
 * SEGMENT_DESCRIPTOR: 全局段号记录表
 * GDTR 特殊寄存器，存储GDT的基本信息
 * limit_low:低16位限长
 * base_low:段基地址的低16位
 * base_mid:段基地址的中间8位
 * access_right:段的管理属性
 * limit_high:高16位限长
 * base_high:段基地址的高8位
*/
struct SEGMENT_DESCRIPTOR {
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
};

/**
 * idt: Interrupt desciptor table 中断记录表，记录了0~255的中断号码与调用函数的对应关系。
 * short offset_low：中断处理程序入口地址的低 16 位。
 * short selector：代码段选择子。
 * char dw_count：双字计数。通常设置为 0。对于 32 位中断门，这个字段被保留且无实际用途。对于 16 位中断门，可能会用于指定参数个数，但在现代 32 位系统中几乎不用。
 * char access_right：访问权限和属性。定义中断门的类型和特权级别等属性，如是否是中断门、陷阱门或任务门，以及门的特权级别（Privilege Level）。
 * short offset_high：中断处理程序入口地址的高 16 位。
*/
struct GATE_DESCRIPTOR {
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
};

void init_gdtidt(void){
    struct SEGMENT_DESCRIPTOR *gdt = (struct SEGMENT_DESCRIPTOR *) 0x00270000;
    struct GATE_DESCRIPTOR *idt = (struct GATE_DESCRIPTOR *) 0x0026f800;
    int i;

    /* GDT 的初始化 */
    for (i = 0; i < 8192; i++){
        set_segmdesc(gdt + i, 0, 0, 0);
    }
    /* 段号为1，上限值为4GB，表示CPU所能管理的全部内存本身*/
    set_segmdesc(gdt + 1, 0xffffffff, 0x00000000, 0x4092);
    /* 段号为2，大小为512KB，地址是0x00280000*/
    set_segmdesc(gdt + 2, 0x0007ffff, 0x00280000, 0x409a);
    load_gdtr(0xffff, 0x00270000); 
    /* IDT 的初始化 */

    for(i = 0; i < 256; i++){
        set_gatedesc(idt + i, 0, 0, 0);
    }
    load_idtr(0x7ff, 0x0026f800);

    return;
}

void set_segmdesc(struct SEGMENT_DESCRIPTOR *sd, unsigned int limit, int base, int ar){
    /**
     * sd:指向要设置的段描述符的指针
     * limit:段的限长，表示段的大小
     * base:段的基地址，表示段的起始地址
     * ar:段的访问权限和属性(Access Right)
    */
    if (limit > 0xfffff){
        ar |= 0x8000; /*  G_bit = 1 */
        limit /= 0x1000;
    }
    sd->limit_low = limit & 0xffff;
    sd->base_low = base & 0xffff;
    sd->base_mid = (base >> 16) & 0xff;
    sd->access_right = ar & 0xff;
    sd->limit_high = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
    sd->base_high = (base >> 24) & 0xff;
    return;
}

void set_gatedesc(struct GATE_DESCRIPTOR *gd, int offset, int selector, int ar){
    gd->offset_low = offset & 0xffff;
    gd->selector = selector;
    gd->dw_count = (ar >> 8) & 0xff;
    gd->access_right = ar & 0xff;
    gd->offset_high = (offset >> 16) & 0xffff;
    return;
}