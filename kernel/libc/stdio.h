#pragma once

#include "../ANSI.h"

//#include "libc/printf.hpp"
#include "../e9print.hpp"

void putchar_(char character)
{
    e9_putc(character);
}