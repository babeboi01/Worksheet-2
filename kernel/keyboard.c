#include "keyboard.h"
#include "io.h"
#include "terminal.h"

static const char sc_ascii[] = {
  0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
  '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
  'a','s','d','f','g','h','j','k','l',';','\'','`',0,'\\','z',
  'x','c','v','b','n','m',',','.','/',0,'*',0,' '
};

void keyboard_init() {}

void keyboard_isr() {
    u8int sc = inb(0x60);
    if (!(sc & 0x80)) {
        char c = sc_ascii[sc];
        if (c)
            terminal_put(c);
    }
}
