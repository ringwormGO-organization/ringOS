#pragma once

#include <stdint.h>

#include "kernelUtil.h"
#include "e9print.hpp"

void boot_copy(uint64_t revision, char* name, char* version);
void kernel_address_copy(uint64_t revision, uint64_t physical_base, uint64_t virtual_base);
void hhdm_copy(uint64_t revision, uint64_t offset);
void memory_copy(uint64_t revision, uint64_t entry_count);
void mem_entry_copy(uint64_t entry_count, uint64_t base, uint64_t base2, char* memory_type);
void framebuffer_start_copy(uint64_t revision, uint64_t framebuffer_count);
void framebuffer_copy(void* address, uint16_t width, uint16_t height, uint16_t pitch, 
                        uint16_t bpp, uint8_t memory_model, uint8_t red_mask_size, 
                        uint8_t red_mask_shift, 
                        uint8_t green_mask_size, uint8_t green_mask_shift, 
                        uint8_t blue_mask_size, uint8_t blue_mask_shift, uint64_t edid_size,
                        void* edid);
void file_copy(uint64_t revision, limine_file* file); /* broken */
void moduels_copy(uint64_t revision, uint64_t module_count, limine_file** f); /* broken */
void rsdp_copy(uint64_t revision, void* address);
void smbios_copy(uint64_t revision, void* entry32, void* entry64);
void efi_table_copy(uint64_t revision, void* address);
void boot_time_copy(uint64_t revision, int64_t time);
void smp_copy(uint64_t revision, uint32_t flags, uint32_t bsp_lapic_id, uint32_t cpu_count);
void smp_cpu_copy(uint64_t extra_argument, limine_goto_address goto_address, uint64_t reserved, 
                    uint32_t processor_id, uint32_t lapic_id);
void terminal_copy(uint64_t revision, uint64_t terminal_count);
void terminal_framebuffer_copy(uint32_t columns, uint32_t rows, limine_framebuffer* framebuffer);