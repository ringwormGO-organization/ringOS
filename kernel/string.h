
#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* https://www.techcrashcourse.com/2016/02/c-program-to-implement-your-own-itoa-function.html */
void reverse(char str[], int len);
char* itoa(int num, char* str, int base);
/* https://www.techcrashcourse.com/2016/02/c-program-to-implement-your-own-itoa-function.html */

const char* to_string(uint64_t value);
const char* to_string_int(int64_t value);
const char* to_hstring64(uint64_t value);
const char* to_hstring32(uint32_t value);
const char* to_hstring16(uint16_t value);
const char* to_hstring8(uint8_t value);