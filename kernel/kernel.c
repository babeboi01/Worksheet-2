#include "terminal.h"
#include "interrupts.h"
#include "keyboard.h"

void kernel_main() {
    terminal_init();
    terminal_write("MyOS Booting...\n");

    interrupts_install_idt();
    keyboard_init();

    terminal_write("Ready.\n> ");

    while (1) {
        terminal_run();  // you will implement
    }
}
