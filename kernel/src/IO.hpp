#pragma once
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
void outw(unsigned short int port, unsigned short int value);
uint8_t inb(uint16_t port);

unsigned char inportb(unsigned int port);
unsigned long long inportl(unsigned long long port);
unsigned long long inportw(unsigned short int port);
void outportb(unsigned int port, unsigned char value);
void outportw(unsigned short int port, unsigned short int data);
void outportl(unsigned long long port, unsigned long long data);

void io_wait();