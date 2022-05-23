/* Credits to Moldytzu */

#pragma once

#include <stdint.h>

#include "../kernelUtil.h"
#include "../memory/memory.hpp"

#define pack __attribute__((__packed__))
#define toMB(x) ((x) / 1024 / 1024)
#define toKB(x) ((x) / 1024)
#define align(val, alg) (val + (alg - (val % alg)))
#define alignD(val, alg) (align(val, alg) - alg)
#define unsafe_cast(val, type) (*(type *)&val)
#define iasm asm volatile
#define ifunc static inline __attribute__((always_inline))
#define doptimize __attribute__((optimize("O0")))
#define between(a, b, c) (((uint64_t)(a) >= (uint64_t)(b)) && ((uint64_t)(a) <= (uint64_t)(c)))

struct mm_pool
{
    uint64_t total;         // total memory
    uint64_t available;     // available memory
    uint64_t used;          // used memory
    bool full;              // if there isn't any available memory available
    void *base;             // base address of the physical memory in the pool
    void *allocableBase;    // base address of the allocable memory in the pool
    size_t pageIndex;       // page index
    size_t bitmapReserved;  // bytes reserved for the bitmap
    size_t bitmapByteIndex; // byte in the bitmap
    uint8_t bitmapBitIndex; // bit in the byte in the bitmap
    uint8_t *bitmapBase;    // base pointer of the bitmap
};

bool mmIsFreePage(struct mm_pool *pool, size_t page);
void mmDeallocatePages(void *address, size_t pages);
void mmDeallocatePage(void *address);
void mmDeallocatePagePool(struct mm_pool *pool, void *address);
void *mmAllocatePage();
void *mmAllocatePages(size_t pages);
void *mmAllocatePagePool(struct mm_pool *pool);
void *mmAllocatePagePoolIndex(struct mm_pool *pool, size_t page);
void *mmAllocatePagesPool(struct mm_pool *pool, size_t pages);
void pmmInit();
struct mm_pool *mmGetPools();
struct mm_pool mmGetTotal();
