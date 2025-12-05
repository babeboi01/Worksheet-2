global common_interrupt_handler
extern interrupt_handler

common_interrupt_handler:
    pusha
    push ds
    push es
    push fs
    push gs

    push dword [esp+44] ; interrupt number
    call interrupt_handler

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 4
    iretd
