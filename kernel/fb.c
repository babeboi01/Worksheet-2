#include "fb.h"
#include "io.h"
#include "types.h"

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5
#define FB_MAX_ROWS     25
#define FB_MAX_COLS     80

static int cursor_row = 0;
static int cursor_col = 0;

/* VGA text-mode memory starts here */
static volatile char *fb = (char *)0xB8000;

static void fb_move_cursor() {
    int pos = cursor_row * FB_MAX_COLS + cursor_col;

    outb(FB_COMMAND_PORT, 14);
    outb(FB_DATA_PORT,   (pos >> 8) & 0xFF);
    outb(FB_COMMAND_PORT, 15);
    outb(FB_DATA_PORT,   pos & 0xFF);
}

void fb_clear() {
    for (int i = 0; i < FB_MAX_ROWS * FB_MAX_COLS; i++) {
        fb[i * 2] = ' ';
        fb[i * 2 + 1] = 0x07;
    }
    cursor_row = 0;
    cursor_col = 0;
    fb_move_cursor();
}

void fb_write_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        int pos = cursor_row * FB_MAX_COLS + cursor_col;
        fb[pos * 2] = c;
        fb[pos * 2 + 1] = 0x07;
        cursor_col++;
    }

    if (cursor_col >= FB_MAX_COLS) {
        cursor_col = 0;
        cursor_row++;
    }

    if (cursor_row >= FB_MAX_ROWS) {
        cursor_row = 0; // simple wrap for Worksheet 2
    }

    fb_move_cursor();
}
