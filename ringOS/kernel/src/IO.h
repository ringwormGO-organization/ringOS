#pragma once
#include <stdint.h>

void outb (uint16_t port, uint8_t value);
void outw(unsigned short int port, unsigned short int value);
uint8_t inb(uint16_t port);
void io_wait();