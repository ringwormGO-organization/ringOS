#include "io.h"

void outb(uint16_t port, uint8_t value)
{
    __asm__ __volatile__ ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void outw(unsigned short int port, unsigned short int value)
{
    __asm__ __volatile__ ("outw %%ax, %%dx"
				 :
				 : "d"(port), "a"(value));
}

uint8_t inb(uint16_t port)
{
    uint8_t returnVal;
    __asm__ __volatile__ ("inb %1, %0"
    : "=a"(returnVal)
    : "Nd"(port));
    return returnVal;
}

void io_wait()
{
    __asm__ __volatile__ ("outb %%al, $0x80" : : "a"(0));
}
