#pragma once

#include <stdint.h>
#include <stddef.h>
#include "limine.h"
#include "e9print.hpp"

#include "gdt/gdt.hpp"
#include "idt/idt.hpp"
#include "paging/physical_memory_manager.hpp"
#include "paging/virtual_memory_m.hpp"
#include "memory/malloc.hpp"

#include "copy.hpp"
/* #include "libc/stdio.h" */ /* need to fix */
#include "libc/libc/string.hpp"
#include "Settings.h"

static char *get_memmap_type(uint64_t type);
void print_file(struct limine_file* file);

typedef struct Bootloader
{
    uint64_t revision;
    char name[50];
    char version[10];
} bootloader ;

typedef struct KernelAddress
{
    uint64_t revision;
    uint64_t physical_base;
    uint64_t virtual_base;
} kernel_address ;

typedef struct HHDM
{
    uint64_t revision;
    uint64_t offset;
} Hhdm ;

typedef struct MemoryMap
{
    uint64_t revision;
    uint64_t entry_count;

    uint64_t entry_base;
    uint64_t entry_base2;

    char memory_type[100];
} mem_map ;

typedef struct Framebuffer
{
    uint64_t revision;
    uint64_t framebuffer_count;

    unsigned int address; /* from void* changed to unsigned int */
    uint16_t width;
    uint16_t height;
    uint16_t pitch;
    uint16_t bpp;

    uint8_t memory_model;
    uint8_t red_mask_size;
    uint8_t red_mask_shift;
    uint8_t green_mask_size;
    uint8_t green_mask_shift;
    uint8_t blue_mask_size;
    uint8_t blue_mask_shift;

    uint64_t edid_size;
    unsigned int edid; /* from void* changed to unsigned int */
} framebuffer ;

typedef struct KernelFile
{
    uint64_t revision;
    limine_file* file;
} kernel_file ;

typedef struct Modules
{
    uint64_t revision;
    uint64_t module_count;
    limine_file** mdl;
} modules ;

typedef struct RSDP
{
    uint64_t revision;
    void* address;
} Rsdp ;

typedef struct SMBIOS
{
    uint64_t revision;
    void* entry32;
    void* entry64;
} sm_bios ;

typedef struct EFI_System_Table
{
    bool isPresent;

    uint64_t revision;
    void* address;    
} efi_system_table ;

typedef struct BootTime
{
    uint64_t revision;
    int64_t time;
} boot_time ;

typedef struct SMP
{
    uint64_t revision;
    uint32_t flags;
    uint32_t bsp_lapic_id;
    uint64_t cpu_count;

    uint64_t extra_argument;
    limine_goto_address goto_address;
    uint64_t reserved;

    uint32_t processor_id;
    uint32_t lapic_id;
} Smp ;

typedef struct LimineTerminal
{
    uint64_t revision;
    uint64_t terminal_count;

    uint32_t columns;
    uint32_t rows;
    limine_framebuffer* framebuffer;

    limine_terminal_write write;
} terminal ;