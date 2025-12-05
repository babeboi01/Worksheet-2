#include "input_buffer.h"
#include "keyboard.h"

static char buffer[INPUT_BUFFER_SIZE];
static int head = 0;
static int tail = 0;

void input_put(char c) {
    int next = (head + 1) % INPUT_BUFFER_SIZE;
    if (next != tail) {
        buffer[head] = c;
        head = next;
    }
}

int getc_nonblock() {
    if (head == tail)
        return -1;  // empty

    char c = buffer[tail];
    tail = (tail + 1) % INPUT_BUFFER_SIZE;
    return c;
}

int readline(char *out, int max) {
    int count = 0;

    while (1) {
        int c = getc_nonblock();
        if (c == -1)
            continue;

        if (c == '\n') {
            out[count] = 0;
            return count;
        }

        if (count < max - 1) {
            out[count++] = c;
        }
    }
}

