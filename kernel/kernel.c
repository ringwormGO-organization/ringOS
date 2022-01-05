#include "stivale2.h"
#include "cstr.h"

static uint8_t stack[0x4000];

static struct stivale2_header_tag_terminal terminal = {
  .tag = {
    .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
    .next = 0
  },
  .flags = 0
};


static struct stivale2_struct_tag_framebuffer buff = {
  .tag = {
    .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
    .next = (uint64_t)&terminal
  },
  .framebuffer_height = STIVALE2_MMAP_FRAMEBUFFER,
  .framebuffer_width = 0,
  .framebuffer_bpp = 0
};

typedef struct Framebuffer
{
    uint64_t framebuffer_addr;
    uint32_t height;
    uint32_t width;
    uint32_t pitch;

} Framebuffer;

__attribute__((section(".stivale2hdr"), used)) 
static struct stivale2_header header = {
  .entry_point = 0,
  .stack = (uint64_t)&stack + sizeof(stack),
  .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
  .tags = (uint64_t)&buff
};

#include "basics.h"
#include "io.h"
#include "pci.h"

void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;) {
        // If the tag pointer is NULL (end of linked list), we did not find
        // the tag. Return NULL to signal this.
        if (current_tag == NULL) {
            return NULL;
        }
 
        // Check whether the identifier matches. If it does, return a pointer
        // to the matching tag.
        if (current_tag->identifier == id) {
            return current_tag;
        }
 
        // Get a pointer to the next tag in the linked list and repeat.
        current_tag = (void *)current_tag->next;
    }
}

int strcmp(char* str1,char* str2,int len)
{
  int status = 1;
  for (int i = 0; i < len; i++)
  {
    if(str1[i] != str2[i])
    {
      status = 0;
      break;
    }
  }
  return status;
}

/*struct stivale2_struct_tag_memmap memmap = {
    static truct stivale2_tag tag;      // Identifier: 0x2187f79e8612de07
    uint64_t entries;             // Count of memory map entries
    struct stivale2_mmap_entry memmap[];  // Array of memory map entries
};

struct stivale2_struct_tag_memmap memmap2 = {
    struct stivale2_tag tag;      // Identifier: 0x2187f79e8612de07
    uint64_t entries;             // Count of memory map entries
    struct stivale2_mmap_entry memmap[];  // Array of memory map entries
};
struct stivale2_mmap_entry mapentry = {
    uint64_t base;      // Physical address of base of the memory section
    uint64_t length;    // Length of the section
    uint32_t type;      // Type (described below)
    uint32_t unused;
};

enum stivale2_mmap_type {
    uint32_t USABLE                 = 1,
    uint32_t RESERVED               = 2,
    uint32_t ACPI_RECLAIMABLE       = 3,
    uint32_t ACPI_NVS               = 4,
    uint32_t BAD_MEMORY             = 5,
    uint32_t BOOTLOADER_RECLAIMABLE = 0x1000,
    uint32_t KERNEL_AND_MODULES     = 0x1001,
    uint32_t FRAMEBUFFER            = 0x1002
};*/

void _start(struct stivale2_struct* stivale2) {
    struct stivale2_struct_tag_terminal *term_str_tag;
    term_str_tag = stivale2_get_tag(stivale2, STIVALE2_STRUCT_TAG_TERMINAL_ID);
    if(term_str_tag == NULL)
    {
      asm("cli");
      asm("hlt");
    }
    void *term_write_ptr = (void *)term_str_tag->term_write;
    void (*term_write)(const char *string, size_t length) = term_write_ptr;

    struct stivale2_struct_tag_rsdp *rsdp_tag;
    rsdp_tag = stivale2_get_tag(stivale2, STIVALE2_STRUCT_TAG_RSDP_ID);
    if(rsdp_tag != NULL)
    {
      struct ACPI_RSDP* rsdp = (ACPI_RSDP*)rsdp_tag->rsdp;
      ACPI_SDTHeader* xsdt = (ACPI_SDTHeader*)rsdp->xsdt_address;
      MCFGHeader* mcfg = (MCFGHeader*)ACPI_FindTable(xsdt,(char*)"MCFG");
      if(mcfg != 0)
      {
        EnumeratePCI(mcfg,term_write);
      }
    }

    /*Framebuffer framebuffer;//creates framebuffer structure
    framebuffer.framebuffer_addr = stivale->framebuffer_addr;//get framebuffer address from stivale
    framebuffer.height = stivale->framebuffer_height;//get height of screen from stivale
    framebuffer.width = stivale->framebuffer_width;
    framebuffer.pitch = stivale->framebuffer_pitch;*/
    
    term_write("Welcome to ringOS!\n\r", 21);
    term_write(rsdp_tag->rsdp,8);

    term_write(to_string((uint64_t)buff.framebuffer_height), 8);
    
    asm("cli");
    asm ("hlt");
}