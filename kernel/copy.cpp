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

void file_copy(uint64_t revision, limine_file* file) /* broken */
{
    kernel_file* kf;

    kf->revision = revision;
    kf->file = file;

    #ifdef WALL_OF_TEXT
        e9_printf("Kernel file feature, revision %d", kf->revision);
        print_file(kf->file);
    #endif
}

void moduels_copy(uint64_t revision, uint64_t module_count, limine_file** f) /* broken */
{
    modules* mdl; /* can't use word module because it is c++20 keyword */

    mdl->revision = revision;
    mdl->module_count = module_count;
    mdl->mdl = f;

    #ifdef WALL_OF_TEXT
        e9_printf("Modules feature, revision %d", mdl->revision);
        e9_printf("%d module(s)", mdl->module_count);
        for (size_t i = 0; i < mdl->module_count; i++) 
        {
            limine_file* new_module = mdl->mdl[i];
            print_file(new_module);
        }
    #endif
}

void rsdp_copy(uint64_t revision, void* address)
{
    Rsdp rsdp;

    rsdp.revision = revision;
    rsdp.address = address;

    #ifdef WALL_OF_TEXT
        e9_printf("RSDP feature, revision %d", rsdp.revision);
        e9_printf("RSDP at: %x", rsdp.address);
    #endif    
}

void smbios_copy(uint64_t revision, void* entry32, void* entry64)
{
    sm_bios smbios;

    smbios.revision = revision;
    smbios.entry32 = entry32;
    smbios.entry64 = entry64;

    #ifdef WALL_OF_TEXT
        e9_printf("SMBIOS feature, revision %d", smbios.revision);
        e9_printf("SMBIOS 32-bit entry at: %x", smbios.entry32);
        e9_printf("SMBIOS 64-bit entry at: %x", smbios.entry64);
    #endif
}

void efi_table_copy(uint64_t revision, void* address)
{
    efi_system_table table;

    if (table.isPresent == true)
    {
        table.revision = revision;
        table.address = address;

        #ifdef WALL_OF_TEXT
            e9_printf("EFI system table feature, revision %d", table.revision);
            e9_printf("EFI system table at: %x", table.address);
        #endif
    }

    else
    {
        e9_printf("EFI system table is not present! Also check why this function is called if %s",
                    "it is not present! Exiting function...");
        return;
    }
}

void boot_time_copy(uint64_t revision, int64_t time)
{
    boot_time bt;

    bt.revision = revision;
    bt.time = time;

    #ifdef WALL_OF_TEXT
        e9_printf("Boot time feature, revision %d", bt.revision);
        e9_printf("Boot time: %d", bt.time);
    #endif
}

void smp_copy(uint64_t revision, uint32_t flags, uint32_t bsp_lapic_id, uint32_t cpu_count)
{
    Smp smp;

    smp.revision = revision;
    smp.flags = flags;
    smp.bsp_lapic_id = bsp_lapic_id;
    smp.cpu_count = cpu_count;

    #ifdef WALL_OF_TEXT
        e9_printf("SMP feature, revision %d", smp.revision);
        e9_printf("Flags: %x", smp.flags);
        e9_printf("BSP LAPIC ID: %x", smp.bsp_lapic_id);
        e9_printf("CPU count: %d", smp.cpu_count);
    #endif
}

void smp_cpu_copy(uint64_t extra_argument, limine_goto_address goto_address, uint64_t reserved, 
                    uint32_t processor_id, uint32_t lapic_id)
{
    Smp smp2;

    smp2.extra_argument = extra_argument;
    smp2.goto_address = goto_address;
    smp2.reserved = reserved;

    smp2.processor_id = processor_id;
    smp2.lapic_id = lapic_id;

    #ifdef WALL_OF_TEXT
        e9_printf("Processor ID: %x", smp2.processor_id);
        e9_printf("LAPIC ID: %x", smp2.lapic_id);
    #endif
}

void terminal_copy(uint64_t revision, uint64_t terminal_count)
{
    terminal term;

    term.revision = revision;
    term.terminal_count = terminal_count;

    #ifdef WALL_OF_TEXT
        e9_printf("Terminal feature, revision %d", term.revision);
        e9_printf("%d terminal(s)", term.terminal_count);
    #endif
}

void terminal_framebuffer_copy(uint32_t columns, uint32_t rows, limine_framebuffer* framebuffer)
{
    terminal termi; /* it is not real termi */

    termi.columns = columns;
    termi.rows = rows;
    termi.framebuffer = framebuffer;

    #ifdef WALL_OF_TEXT
        e9_printf("Columns: %d", termi.columns);
        e9_printf("Rows: %d", termi.rows);
        e9_printf("Using framebuffer: %x", termi.framebuffer);
    #endif
}