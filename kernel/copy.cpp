#include "copy.hpp"

void boot_copy(uint64_t revision, char* name, char* version)
{
    bootloader boot;

    boot.revision = revision;
    strcpy(boot.name, name);
    strcpy(boot.version, version);

    #ifdef WALL_OF_TEXT
        e9_printf("Bootloader info feature, revision %d", boot.revision);
        e9_printf("Bootloader name: %s", boot.name);
        e9_printf("Bootloader version: %s", boot.version);
    #endif
}

void kernel_address_copy(uint64_t revision, uint64_t physical_base, uint64_t virtual_base)
{
    kernel_address address;

    address.revision = revision;
    address.physical_base = physical_base;
    address.virtual_base = virtual_base;

    #ifdef WALL_OF_TEXT
        e9_printf("Kernel address feature, revision %d", address.revision);
        e9_printf("Physical base: %x", address.physical_base);
        e9_printf("Virtual base: %x", address.virtual_base);
    #endif
}

void hhdm_copy(uint64_t revision, uint64_t offset)
{
    Hhdm hhdm;

    hhdm.revision = revision;
    hhdm.offset = offset;
    
    #ifdef WALL_OF_TEXT
        e9_printf("HHDM feature, revision %d", hhdm.revision);
        e9_printf("Higher half direct map at: %x", hhdm.offset);
    #endif
}

void memory_copy(uint64_t revision, uint64_t entry_count)
{
    mem_map map;

    map.revision = revision;
    map.entry_count = entry_count;

    #ifdef WALL_OF_TEXT
        e9_printf("Memory map feature, revision %d", map.revision);
        e9_printf("%d memory map entries", map.entry_count);
    #endif   
}

void mem_entry_copy(uint64_t base, uint64_t base2, char* memory_type)
{
    mem_map map2;

    for (size_t i = 0; i < map2.entry_count; i++)
    {
        map2.entry_base = base;
        map2.entry_base2 = base2;
        strcpy(map2.memory_type, memory_type);

        #ifdef WALL_OF_TEXT
            e9_printf("%x->%x %s", map2.entry_base, map2.entry_base2, map2.memory_type);
        #endif

    }
}

void framebuffer_start_copy(uint64_t revision, uint64_t framebuffer_count)
{
    framebuffer frame;

    frame.revision = revision;
    frame.framebuffer_count = framebuffer_count;

    #ifdef WALL_OF_TEXT
        e9_printf("Framebuffers feature, revision %d", frame.revision);
        e9_printf("%d framebuffer(s)", frame.framebuffer_count);
    #endif
}

void framebuffer_copy(unsigned int address, uint16_t width, uint16_t height, uint16_t pitch, 
                        uint16_t bpp, uint8_t memory_model, uint8_t red_mask_size, 
                        uint8_t red_mask_shift, 
                        uint8_t green_mask_size, uint8_t green_mask_shift, 
                        uint8_t blue_mask_size, uint8_t blue_mask_shift, uint64_t edid_size,
                        unsigned int edid)

{
    framebuffer fb;

    for (size_t i = 0; i < fb.framebuffer_count; i++) 
    {
        fb.address = address;
        fb.width = width;
        fb.height = height;
        fb.pitch = pitch;
        fb.bpp = bpp;

        fb.memory_model = memory_model;
        fb.red_mask_size = red_mask_size;
        fb.red_mask_shift = red_mask_shift;
        fb.green_mask_size = green_mask_size;
        fb.green_mask_shift = green_mask_shift;
        fb.blue_mask_size = blue_mask_size;
        fb.blue_mask_shift = blue_mask_shift;

        fb.edid_size = edid_size;
        fb.edid = edid;

        #ifdef WALL_OF_TEXT
            e9_printf("Address: %x", fb.address);
            e9_printf("Width: %d", fb.width);
            e9_printf("Height: %d", fb.height);
            e9_printf("Pitch: %d", fb.pitch);
            e9_printf("BPP: %d", fb.bpp);
            e9_printf("Memory model: %d", fb.memory_model);
            e9_printf("Red mask size: %d", fb.red_mask_size);
            e9_printf("Red mask shift: %d", fb.red_mask_shift);
            e9_printf("Green mask size: %d", fb.green_mask_size);
            e9_printf("Green mask shift: %d", fb.green_mask_shift);
            e9_printf("Blue mask size: %d", fb.blue_mask_size);
            e9_printf("Blue mask shift: %d", fb.blue_mask_shift);
            e9_printf("EDID size: %d", fb.edid_size);
            e9_printf("EDID at: %x", fb.edid);
        #endif
    }
}