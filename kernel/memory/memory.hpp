#pragma once

#include <stdint.h>
#include <stddef.h>

void memset(void* start, uint8_t value, uint64_t num);
void memcpy(void *d, const void *s, size_t n);
int memcmp(const void *aptr, const void *bptr, size_t n);
