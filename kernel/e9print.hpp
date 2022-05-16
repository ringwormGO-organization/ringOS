#pragma once

#include <stdarg.h>
#include <stddef.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_ORANGE  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CLEAR "\e[1;1H\e[2J"

extern void (*stivale2_print)(const char *buf, size_t size);

void e9_putc(char c);
void e9_print(const char *msg);
void e9_puts(const char *msg);
void e9_printf(const char *format, ...);