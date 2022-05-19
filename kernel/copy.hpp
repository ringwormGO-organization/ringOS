#pragma once

#include <stdint.h>

#include "kernelUtil.h"
#include "e9print.hpp"

void boot_copy(uint64_t revision, char* name, char* version);
void kernel_address_copy(uint64_t revision, uint64_t physical_base, uint64_t virtual_base);
void hhdm_copy(uint64_t revision, uint64_t offset);
void memory_copy(uint64_t revision, uint64_t entry_count);
void mem_entry_copy(uint64_t base, uint64_t base2, char* memory_type);
void framebuffer_start_copy(uint64_t revision, uint64_t framebuffer_count);
void framebuffer_copy(unsigned int address, uint16_t width, uint16_t height, uint16_t pitch, 
                        uint16_t bpp, uint8_t memory_model, uint8_t red_mask_size, 
                        uint8_t red_mask_shift, 
                        uint8_t green_mask_size, uint8_t green_mask_shift, 
                        uint8_t blue_mask_size, uint8_t blue_mask_shift, uint64_t edid_size,
                        unsigned int edid);