#include "types.h"

struct IDTDescriptor {
    u16int offset_low;
    u16int selector;
    u8int zero;
    u8int type_attr;
    u16int offset_high;
} __attribute__((packed));

struct IDT {
    u16int limit;
    u32int base;
} __attribute__((packed));

void interrupts_install_idt();
