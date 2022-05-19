#pragma once

#include "../paging/physical_memory_manager.hpp"
#include "../paging/virtual_memory_m.hpp"

#define PAGE_SIZE 4096

// Singly linked list nodes for blocks of memory
typedef struct malloc_block {
    uint32_t size;  // Size of this memory block in bytes
    bool free;      // Is this block of memory free?
    struct malloc_block *next;  // Next block of memory
} malloc_block_t;

static malloc_block_t *malloc_list_head = 0;    // Start of linked list
static uint32_t malloc_virt_address     = 0;
static uint32_t malloc_phys_address     = 0;
static uint32_t total_malloc_pages      = 0;

void malloc_init(const uint32_t bytes);
void malloc_split(malloc_block_t *node, const uint32_t size);
void *malloc_next_block(const uint32_t size);
void merge_free_blocks(void);
void malloc_free(void *ptr);