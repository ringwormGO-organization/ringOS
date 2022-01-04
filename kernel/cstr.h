
#pragma once

#include <stdint.h>
#include <stddef.h>


const char* to_string(uint64_t value);
const char* to_string_int(int64_t value);
const char* to_hstring64(uint64_t value);
const char* to_hstring32(uint32_t value);
const char* to_hstring16(uint16_t value);
const char* to_hstring8(uint8_t value);
const char* to_string_decimal(double value, uint8_t decimalPlaces);