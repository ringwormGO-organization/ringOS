#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstddef>

#include "efiMemory.hpp"

uint64_t GetMemorySize(EFI_MEMORY_DESCRIPTOR* mMap, uint64_t mMapEntries, uint64_t mMapDescSize);
void memset(void* start, uint8_t value, uint64_t num);
void memcpy(void *d, const void *s, size_t n);
extern "C" void *memmove(void *dest, const void *src, size_t len);
int memcmp(const void *aptr, const void *bptr, size_t n);