#include <uefi.h>

#include "kernel/bootparam.h"
#include "ELF.h"

/**
 * Load an ELF executable and pass control over for good
 */
int main(int argc, char **argv)
{
    FILE *f;
    char *buff;
    long int size;
    Elf64_Ehdr *elf;
    Elf64_Phdr *phdr;
    uintptr_t entry;
    bootparam_t bootp;
    efi_status_t status;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    int i;

    ST->ConOut->SetAttribute(ST->ConOut, EFI_BROWN);
    printf("Welcome to ringOS POSIX!! \n");
    ST->ConOut->SetAttribute(ST->ConOut, EFI_WHITE);

    /* ---------------------------------------------------------------- */

    /* Memory map */
    efi_memory_descriptor_t *memory_map = NULL, *mement;
    uintn_t memory_map_size=0, map_key=0, desc_size=0;
    const char *types[] = {
        "EfiReservedMemoryType",
        "EfiLoaderCode",
        "EfiLoaderData",
        "EfiBootServicesCode",
        "EfiBootServicesData",
        "EfiRuntimeServicesCode",
        "EfiRuntimeServicesData",
        "EfiConventionalMemory",
        "EfiUnusableMemory",
        "EfiACPIReclaimMemory",
        "EfiACPIMemoryNVS",
        "EfiMemoryMappedIO",
        "EfiMemoryMappedIOPortSpace",
        "EfiPalCode"
    };

    /* get the memory map */
    status = BS->GetMemoryMap(&memory_map_size, NULL, &map_key, &desc_size, NULL);
    if(status != EFI_BUFFER_TOO_SMALL || !memory_map_size) goto err;
    /* in worst case malloc allocates two blocks, and each block might split a record into three, that's 4 additional records */
    memory_map_size += 4 * desc_size;
    memory_map = (efi_memory_descriptor_t*)malloc(memory_map_size);
    if(!memory_map) {
        fprintf(stderr, "unable to allocate memory\n");
        return 1;
    }
    status = BS->GetMemoryMap(&memory_map_size, memory_map, &map_key, &desc_size, NULL);
    if(EFI_ERROR(status)) {
err:    fprintf(stderr, "Unable to get memory map\n");
        return 0;
    }

    printf("Address              Size Type\n");
    for(mement = memory_map; (uint8_t*)mement < (uint8_t*)memory_map + memory_map_size;
        mement = NextMemoryDescriptor(mement, desc_size)) {
            printf("%016x %8d %02x %s\n", mement->PhysicalStart, mement->NumberOfPages, mement->Type, types[mement->Type]);
    }

    free(memory_map);

    /* ---------------------------------------------------------------- */

    /* load the file */
    if((f = fopen("kernel.elf", "r"))) 
    {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        buff = malloc(size + 1);
        if(!buff) 
        {
            fprintf(stderr, "unable to allocate memory\n");
            return 1;
        }
        fread(buff, size, 1, f);
        fclose(f);
    } 
    else 
    {
        fprintf(stderr, "Unable to open file\n");
        return 0;
    }

    /* set up boot parameters passed to the "kernel" */
    memset(&bootp, 0, sizeof(bootparam_t));
    status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    if(!EFI_ERROR(status) && gop) 
    {
        status = gop->SetMode(gop, 0);
        ST->ConOut->Reset(ST->ConOut, 0);
        ST->StdErr->Reset(ST->StdErr, 0);
        if(EFI_ERROR(status)) {
            fprintf(stderr, "unable to set video mode\n");
            return 0;
        }
        bootp.framebuffer = (unsigned int*)gop->Mode->FrameBufferBase;
        bootp.width = gop->Mode->Information->HorizontalResolution;
        bootp.height = gop->Mode->Information->VerticalResolution;
        bootp.pitch = sizeof(unsigned int) * gop->Mode->Information->PixelsPerScanLine;
    } 
    else 
    {
        fprintf(stderr, "unable to get graphics output protocol\n");
        return 0;
    }
    if(argc > 1) 
    {
        bootp.argc = argc - 1;
        bootp.argv = (char**)malloc(argc * sizeof(char*));
        if(bootp.argv) {
            for(i = 0; i < bootp.argc; i++)
                if((bootp.argv[i] = (char*)malloc(strlen(argv[i + 1]) + 1)))
                    strcpy(bootp.argv[i], argv[i + 1]);
            bootp.argv[i] = NULL;
        }
    }

    /* is it a valid ELF executable for this architecture? */
    elf = (Elf64_Ehdr *)buff;
    if(!memcmp(elf->e_ident, ELFMAG, SELFMAG) &&    /* magic match? */
        elf->e_ident[EI_CLASS] == ELFCLASS64 &&     /* 64 bit? */
        elf->e_ident[EI_DATA] == ELFDATA2LSB &&     /* LSB? */
        elf->e_type == ET_EXEC &&                   /* executable object? */
        elf->e_machine == EM_MACH &&                /* architecture match? */
        elf->e_phnum > 0) 
        {                         /* has program headers? */
            /* load segments */
            for(phdr = (Elf64_Phdr *)(buff + elf->e_phoff), i = 0;
                i < elf->e_phnum;
                i++, phdr = (Elf64_Phdr *)((uint8_t *)phdr + elf->e_phentsize)) 
                {
                    if(phdr->p_type == PT_LOAD) 
                    {
                        memcpy((void*)phdr->p_vaddr, buff + phdr->p_offset, phdr->p_filesz);
                        memset((void*)(phdr->p_vaddr + phdr->p_filesz), 0, phdr->p_memsz - phdr->p_filesz);
                    }
                }
            entry = elf->e_entry;
    } 
    else 
    {
        fprintf(stderr, "not a valid ELF executable for this architecture\n");
        return 0;
    }
    /* free resources */
    free(buff);

    /* execute the "kernel" */
    (*((void(* __attribute__((sysv_abi)))(bootparam_t *))(entry)))(&bootp);

    /* failsafe, should never return just in case */
    while(1);

    return 0;
}