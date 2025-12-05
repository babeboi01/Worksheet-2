#ifndef IO_H
#define IO_H

#include "types.h"

static inline void outb(u16int port, u8int value) {
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline u8int inb(u16int port) {
    u8int ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

#endif
