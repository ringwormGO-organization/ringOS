#include "kernelUtil.h"

extern "C" void _start(void);

struct limine_entry_point_request entry_point_request = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0, .response = NULL,

    .entry = _start
};

__attribute__((section(".limine_reqs")))
void *entry_point_req = &entry_point_request;

struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *framebuffer_req = &framebuffer_request;

struct limine_bootloader_info_request bootloader_info_request = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *bootloader_info_req = &bootloader_info_request;

struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *hhdm_req = &hhdm_request;

struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *memmap_req = &memmap_request;

struct limine_kernel_file_request kf_request = {
    .id = LIMINE_KERNEL_FILE_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *kf_req = &kf_request;

struct limine_module_request module_request = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *module_req = &module_request;

struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *rsdp_req = &rsdp_request;

struct limine_smbios_request smbios_request = {
    .id = LIMINE_SMBIOS_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *smbios_req = &smbios_request;

struct limine_efi_system_table_request est_request = {
    .id = LIMINE_EFI_SYSTEM_TABLE_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *est_req = &est_request;

struct limine_boot_time_request boot_time_request = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *boot_time_req = &boot_time_request;

struct limine_kernel_address_request kernel_address_request = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *kernel_address_req = &kernel_address_request;

struct limine_smp_request _smp_request = {
    .id = LIMINE_SMP_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *smp_req = &_smp_request;

struct limine_terminal_request _terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *terminal_req = &_terminal_request;

static char *get_memmap_type(uint64_t type) {
    switch (type) {
        case LIMINE_MEMMAP_USABLE:
            return "Usable";
        case LIMINE_MEMMAP_RESERVED:
            return "Reserved";
        case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
            return "ACPI reclaimable";
        case LIMINE_MEMMAP_ACPI_NVS:
            return "ACPI NVS";
        case LIMINE_MEMMAP_BAD_MEMORY:
            return "Bad memory";
        case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            return "Bootloader reclaimable";
        case LIMINE_MEMMAP_KERNEL_AND_MODULES:
            return "Kernel and modules";
        case LIMINE_MEMMAP_FRAMEBUFFER:
            return "Framebuffer";
        default:
            return "???";
    }
}

static void print_file(struct limine_file *file) {
    e9_printf("File->Revision: %d", file->revision);
    e9_printf("File->Address: %x", file->address);
    e9_printf("File->Size: %x", file->size);
    e9_printf("File->Path: %s", file->path);
    e9_printf("File->CmdLine: %s", file->cmdline);
    e9_printf("File->MediaType: %d", file->media_type);
    e9_printf("File->PartIndex: %d", file->partition_index);
    e9_printf("File->TFTPIP: %d.%d.%d.%d",
              (file->tftp_ip & (0xff << 0)) >> 0,
              (file->tftp_ip & (0xff << 8)) >> 8,
              (file->tftp_ip & (0xff << 16)) >> 16,
              (file->tftp_ip & (0xff << 24)) >> 24);
    e9_printf("File->TFTPPort: %d", file->tftp_port);
    e9_printf("File->MBRDiskId: %x", file->mbr_disk_id);
    e9_printf("File->GPTDiskUUID: %x-%x-%x-%x",
              file->gpt_disk_uuid.a,
              file->gpt_disk_uuid.b,
              file->gpt_disk_uuid.c,
              *(uint64_t *)file->gpt_disk_uuid.d);
    e9_printf("File->GPTPartUUID: %x-%x-%x-%x",
              file->gpt_part_uuid.a,
              file->gpt_part_uuid.b,
              file->gpt_part_uuid.c,
              *(uint64_t *)file->gpt_part_uuid.d);
    e9_printf("File->PartUUID: %x-%x-%x-%x",
              file->part_uuid.a,
              file->part_uuid.b,
              file->part_uuid.c,
              *(uint64_t *)file->part_uuid.d);
}

#define FEAT_START do {
#define FEAT_END } while (0);

extern char kernel_start[];

static void write_shim(const char *s, uint64_t l) {
    struct limine_terminal *terminal = _terminal_request.response->terminals[0];

    _terminal_request.response->write(terminal, s, l);
}

extern "C" void _start(void) 
{
    char kernel_start[1000];

    if (_terminal_request.response) 
    {
        stivale2_print = write_shim;
    }

    e9_printf("\nWe're alive");
    uint64_t kernel_slide = (uint64_t)kernel_start - 0xffffffff80000000;
    e9_printf("Kernel slide: %x", kernel_slide);

    create_descriptor();
    idt_init();

    current_page_directory = (page_directory *)*(uint32_t *)CURRENT_PAGE_DIR_ADDRESS;
    memory_map  = (uint32_t *)MEMMAP_AREA;
    max_blocks  = *(uint32_t *)PHYS_MEM_MAX_BLOCKS;
    used_blocks = *(uint32_t *)PHYS_MEM_USED_BLOCKS;

FEAT_START
    e9_printf("");
    if (bootloader_info_request.response == NULL) {
        e9_printf("Bootloader info not passed");
        break;
    }
    struct limine_bootloader_info_response *bootloader_info_response = bootloader_info_request.response;
    boot_copy(bootloader_info_response->revision, bootloader_info_response->name, bootloader_info_response->version);
FEAT_END

FEAT_START
    e9_printf("");
    if (kernel_address_request.response == NULL) {
        e9_printf("Kernel address not passed");
        break;
    }
    struct limine_kernel_address_response *ka_response = kernel_address_request.response;
    kernel_address_copy(ka_response->revision, ka_response->physical_base, ka_response->virtual_base);
FEAT_END

FEAT_START
    e9_printf("");
    if (hhdm_request.response == NULL) {
        e9_printf("HHDM not passed");
        break;
    }
    struct limine_hhdm_response *hhdm_response = hhdm_request.response;
    hhdm_copy(hhdm_response->revision, hhdm_response->offset);
FEAT_END

FEAT_START
    e9_printf("");
    if (memmap_request.response == NULL) {
        e9_printf("Memory map not passed");
        break;
    }
    struct limine_memmap_response *memmap_response = memmap_request.response;
    memory_copy(memmap_response->revision, memmap_response->entry_count);

    for (size_t i = 0; i < memmap_response->entry_count; i++) 
    {
        struct limine_memmap_entry *e = memmap_response->entries[i];
        mem_entry_copy(e->base, e->base + e->length, get_memmap_type(e->type));
    }
FEAT_END

FEAT_START
    e9_printf("");
    if (framebuffer_request.response == NULL) {
        e9_printf("Framebuffer not passed");
        break;
    }
    struct limine_framebuffer_response *fb_response = framebuffer_request.response;
    framebuffer_start_copy(fb_response->revision, fb_response->framebuffer_count);
    for (size_t i = 0; i < fb_response->framebuffer_count; i++) {
        struct limine_framebuffer *fb = fb_response->framebuffers[i];
        framebuffer_copy((unsigned int)fb->address, fb->width, fb->height, fb->pitch, fb->bpp, fb->memory_model,
                            fb->red_mask_size, fb->red_mask_shift, fb->green_mask_size,
                            fb->green_mask_shift, fb->blue_mask_size, fb->blue_mask_shift, 
                            fb->edid_size, (unsigned int)fb->edid);
    }
FEAT_END

    e9_printf(ANSI_COLOR_RED "\nColor test\n" ANSI_COLOR_RESET);

    for (;;);
}