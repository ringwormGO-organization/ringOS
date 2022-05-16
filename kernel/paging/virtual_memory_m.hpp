#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "physical_memory_manager.hpp"
#include "global_addresses.hpp"
#include "../memory/memory.hpp"

#define PAGES_PER_TABLE 1024
#define TABLES_PER_DIRECTORY 1024
#define PAGE_SIZE 4096

#define PD_INDEX(address) ((address) >> 22)
#define PT_INDEX(address) (((address) >> 12) & 0x3FF) // Max index 1023 = 0x3FF
#define PAGE_PHYS_ADDRESS(dir_entry) ((*dir_entry) & ~0xFFF)    // Clear lowest 12 bits, only return frame/address
#define SET_ATTRIBUTE(entry, attr) (*entry |= attr)
#define CLEAR_ATTRIBUTE(entry, attr) (*entry &= ~attr)
#define TEST_ATTRIBUTE(entry, attr) (*entry & attr)
#define SET_FRAME(entry, address) (*entry = (*entry & ~0x7FFFF000) | address)   // Only set address/frame, not flags

typedef uint32_t pt_entry;  // Page table entry
typedef uint32_t pd_entry;  // Page directory entry
typedef uint32_t physical_address; 
typedef uint32_t virtual_address; 

typedef enum {
    PTE_PRESENT       = 0x01,
    PTE_READ_WRITE    = 0x02,
    PTE_USER          = 0x04,
    PTE_WRITE_THROUGH = 0x08,
    PTE_CACHE_DISABLE = 0x10,
    PTE_ACCESSED      = 0x20,
    PTE_DIRTY         = 0x40,
    PTE_PAT           = 0x80,
    PTE_GLOBAL        = 0x100,
    PTE_FRAME         = 0x7FFFF000,   // bits 12+
} PAGE_TABLE_FLAGS;

typedef enum {
    PDE_PRESENT       = 0x01,
    PDE_READ_WRITE    = 0x02,
    PDE_USER          = 0x04,
    PDE_WRITE_THROUGH = 0x08,
    PDE_CACHE_DISABLE = 0x10,
    PDE_ACCESSED      = 0x20,
    PDE_DIRTY         = 0x40,          // 4MB entry only
    PDE_PAGE_SIZE     = 0x80,          // 0 = 4KB page, 1 = 4MB page
    PDE_GLOBAL        = 0x100,         // 4MB entry only
    PDE_PAT           = 0x2000,        // 4MB entry only
    PDE_FRAME         = 0x7FFFF000,    // bits 12+
} PAGE_DIR_FLAGS;

// Page table: handle 4MB each, 1024 entries * 4096
typedef struct {
    pt_entry entries[PAGES_PER_TABLE];
} page_table;

// Page directory: handle 4GB each, 1024 page tables * 4MB
typedef struct {
    pd_entry entries[TABLES_PER_DIRECTORY];
} page_directory;

static page_directory *current_page_directory = 0;

pt_entry *get_pt_entry(page_table *pt, virtual_address address);
pd_entry *get_pd_entry(page_table *pd, virtual_address address);
pt_entry *get_page(const virtual_address address);

void *allocate_page(pt_entry *page);
void free_page(pt_entry *page);
void flush_tlb_entry(virtual_address address);
void unmap_page(void *virt_address);

bool set_page_directory(page_directory *pd);
bool map_page(void *phys_address, void *virt_address);
bool initialize_virtual_memory_manager(void);
