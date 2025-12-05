#include "terminal.h"
#include "fb.h"
#include "input_buffer.h"

void terminal_init() {
    fb_clear();
    terminal_write("Welcome to my OS!\n");
}

void terminal_write(const char *s) {
    while (*s) {
        fb_write_char(*s++);
    }
}

void terminal_put(char c) {
    fb_write_char(c);
}

void terminal_run() {
    terminal_write("> ");

    char buffer[256];
    while (1) {
        int len = readline(buffer, 256);
        terminal_write("\nYou typed: ");
        terminal_write(buffer);
        terminal_write("\n> ");
    }
}
