#include "interrupts.h"
#include "pic.h"
#include "terminal.h"

extern void load_idt(struct IDT *idt);
extern void interrupt_handler_33();

struct IDTDescriptor idt[256];
struct IDT idt_ptr;

static void set_idt(int num, u32int base) {
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = 0x08;
    idt[num].zero = 0;
    idt[num].type_attr = 0x8E;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
}

void interrupts_install_idt() {
    set_idt(33, (u32int)interrupt_handler_33);

    idt_ptr.base = (u32int)&idt;
    idt_ptr.limit = sizeof(idt) - 1;

    load_idt(&idt_ptr);

    pic_remap(32, 40);
}

void interrupt_handler(u32int interrupt) {
    if (interrupt == 33) {
        keyboard_isr();
        pic_acknowledge(interrupt);
    }
}
