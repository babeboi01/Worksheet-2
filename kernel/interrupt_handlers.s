global load_idt
global interrupt_handler_33
extern common_interrupt_handler

load_idt:
    lidt [esp+4]
    ret

interrupt_handler_33:
    push dword 33
    jmp common_interrupt_handler
