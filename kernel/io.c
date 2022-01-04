#include <stdint.h>
#include "io.h"
//io functions from https://wiki.osdev.org/Inline_Assembly/Examples

void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                : "=a"(ret)
                : "Nd"(port) );
    return ret;
}

void outl(uint16_t port,uint32_t val)
{
    asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
}

uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile ( "inl %1, %0"
                : "=a"(ret)
                : "Nd"(port) );
    return ret;
}