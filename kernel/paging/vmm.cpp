/* Credits to Moldytzu */

#include "vmm.hpp"
#include "pmm.hpp"
#include "../kernelUtil.h"
#include "../idt/idt.hpp"
#include "../gdt/gdt.hpp"

#include "../limine.h"

struct limine_memmap_request memmap_request2 = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0, .response = NULL
};

__attribute__((section(".limine_reqs")))
void *memmap_req2 = &memmap_request2;

mem_map* bootloaderGetMemMap()
{
    mem_map* map;
    return map;
}

struct vmm_page_table* baseTable;

// get indices in the page table of a virtual address
struct vmm_index vmmIndex(uint64_t virtualAddress)
{
    struct vmm_index index;
    index.P = (virtualAddress & ((uint64_t)0x1FF << 12)) >> 12;
    index.PT = (virtualAddress & ((uint64_t)0x1FF << 21)) >> 21;
    index.PD = (virtualAddress & ((uint64_t)0x1FF << 30)) >> 30;
    index.PDP = (virtualAddress & ((uint64_t)0x1FF << 39)) >> 39;
    index.PML4 = (virtualAddress & ((uint64_t)0x1FF << 48)) >> 48;
    return index;
}

// initialize the virtual memory manager
void vmmInit()
{
    baseTable = vmmCreateTable(true); // create the base table with hhdm
    vmmSwap(baseTable);               // swap the table
}

// set flags of some entries given by the indices
void vmmSetFlags(struct vmm_page_table *table, struct vmm_index index)
{
    struct vmm_page_table *pml4, *pdp, *pd, *pt;
    uint64_t currentEntry;

    pml4 = table;

    currentEntry = pml4->entries[index.PDP];         // index pdp
    pml4->entries[index.PDP] = currentEntry;         // write the entry in the table

    pdp = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue
    currentEntry = pdp->entries[index.PD];                               // index further
    pdp->entries[index.PD] = currentEntry;                               // write the entry in the table

    pd = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue
    currentEntry = pd->entries[index.PT];                               // index further
    pd->entries[index.PT] = currentEntry;                               // write the entry in the table

    pt = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue
    currentEntry = pt->entries[index.P];                                // index further
    pt->entries[index.P] = currentEntry;                                // write the entry in the table
}

// map a virtual address to a physical address in a page table
void vmmMap(struct vmm_page_table *table, void *virtualAddress, void *physicalAddress)
{
    struct vmm_index index = vmmIndex((uint64_t)virtualAddress); // get the offsets in the page tables
    struct vmm_page_table *pml4, *pdp, *pd, *pt;
    uint64_t currentEntry;

    pml4 = table;

    currentEntry = pml4->entries[index.PDP];           // index pdp
    if (!vmmGetFlag(&currentEntry, VMM_ENTRY_PRESENT)) // if there isn't any page present there, we generate it
    {
        pdp = (vmm_page_table*)mmAllocatePage();                             // allocate table
        memset64(pdp, 0, VMM_PAGE / sizeof(uint64_t));      // clear it
        vmmSetAddress(&currentEntry, (uint64_t)pdp >> 12);  // set it's address
        vmmSetFlag(&currentEntry, VMM_ENTRY_PRESENT, true); // present
        pml4->entries[index.PDP] = currentEntry;            // write the entry in the table
    }
    else
        pdp = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pdp->entries[index.PD];             // index pd
    if (!vmmGetFlag(&currentEntry, VMM_ENTRY_PRESENT)) // if there isn't any page present there, we generate it
    {
        pd = (vmm_page_table*)mmAllocatePage();                              // allocate table
        memset64(pd, 0, VMM_PAGE / sizeof(uint64_t));       // clear it
        vmmSetAddress(&currentEntry, (uint64_t)pd >> 12);   // set it's address
        vmmSetFlag(&currentEntry, VMM_ENTRY_PRESENT, true); // present
        pdp->entries[index.PD] = currentEntry;              // write the entry in the table
    }
    else
        pd = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pd->entries[index.PT];              // index pt
    if (!vmmGetFlag(&currentEntry, VMM_ENTRY_PRESENT)) // if there isn't any page present there, we generate it
    {
        pt = (vmm_page_table*)mmAllocatePage();                              // allocate table
        memset64(pt, 0, VMM_PAGE / sizeof(uint64_t));       // clear it
        vmmSetAddress(&currentEntry, (uint64_t)pt >> 12);   // set it's address
        vmmSetFlag(&currentEntry, VMM_ENTRY_PRESENT, true); // present
        pd->entries[index.PT] = currentEntry;               // write the entry in the table
    }
    else
        pt = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pt->entries[index.P];                           // index p
    vmmSetAddress(&currentEntry, (uint64_t)physicalAddress >> 12); // set the address to the physical one
    vmmSetFlag(&currentEntry, VMM_ENTRY_PRESENT, true);            // present
    pt->entries[index.P] = currentEntry;                           // write the entry in the table

    vmmSetFlags(table, index); // set the flags
}

// unmap a virtual address
void vmmUnmap(struct vmm_page_table *table, void *virtualAddress)
{
    struct vmm_index index = vmmIndex((uint64_t)virtualAddress); // get the offsets in the page tables
    struct vmm_page_table *pdp, *pd, *pt;

    uint64_t currentEntry = table->entries[index.PDP]; // index pdp
    pdp = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12);

    currentEntry = pdp->entries[index.PD]; // index pd
    pd = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12);

    currentEntry = pd->entries[index.PT]; // index pt
    pt = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12);

    currentEntry = pt->entries[index.P];                 // index p
    vmmSetFlag(&currentEntry, VMM_ENTRY_PRESENT, false); // unvalidate page
    pt->entries[index.P] = currentEntry;                 // write the entry in the table
}

// get the base table aka kernel table
void *vmmGetBaseTable()
{
    return baseTable;
}

// get physical address of a virtual address
void *vmmGetPhys(struct vmm_page_table *table, void *virtualAddress)
{
    // get physical memory address form virtual memory address
    struct vmm_index index = vmmIndex((uint64_t)virtualAddress); // get the offsets in the page tables
    struct vmm_page_table *pdp, *pd, *pt;

    uint64_t currentEntry = table->entries[index.PDP];                   // index pdp
    pdp = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pdp->entries[index.PD];                              // index pd
    pd = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pd->entries[index.PT];                               // index pt
    pt = (struct vmm_page_table *)(vmmGetAddress(&currentEntry) << 12); // continue

    currentEntry = pt->entries[index.P];                                                              // index p
    return (void *)(vmmGetAddress(&currentEntry) * VMM_PAGE + ((uint64_t)virtualAddress % VMM_PAGE)); // get the address
}

// create a new table
struct pack vmm_page_table *vmmCreateTable(bool full)
{
    // create a new table to use as a base for everything
    register void *newTable = mmAllocatePage();         // allocate a page for the new table
    memset64(newTable, 0, VMM_PAGE / sizeof(uint64_t)); // clear the paging table

    limine_memmap_entry **memmaps = memmap_request2.response->entries;
    uint64_t memmap_count = memmap_request2.response->entry_count;

    kernel_address* ka;
    framebuffer* fb;

#ifdef K_VMM_DEBUG
    uint64_t a = mmGetTotal().available;
#endif

    mem_map *map; // get the memory map

    if (full)
    {
        Hhdm* hhdm;

        // map all memory map entries
        for (uint64_t i = 0; i < map->entry_count; i++)
        {
            for (uint64_t j = 0; j < memmaps[i]->length; j += 4096)
            {
                vmmMap((vmm_page_table*)newTable, (void *)memmaps[i]->base + j, (void *)memmaps[i]->base + j);
                vmmMap((vmm_page_table*)newTable, (void *)memmaps[i]->base + j + (uint64_t)hhdm, (void *)memmaps[i]->base + j);
            }
        }
    }

    vmmMap((vmm_page_table*)newTable, (vmm_page_table*)newTable, (vmm_page_table*)newTable);                 // map the table
    vmmMap((vmm_page_table*)newTable, (void *)create_descriptor, (void *)create_descriptor);                 // map the gdt

    return (vmm_page_table*)newTable; // return the created table
}
