#pragma once

#include <stdint.h>

#include "BMPImageFile.h"
#include "BasicRenderer.hpp"
#include "cstr.hpp"
#include "efiMemory.hpp"
#include "memory.hpp"
#include "Bitmap.hpp"
#include "paging/PageFrameAllocator.hpp"
#include "paging/PageMapIndexer.hpp"
#include "paging/paging.hpp"
#include "paging/PageTableManager.hpp"
#include "userinput/mouse.hpp"
#include "acpi.hpp"
#include "pci.hpp"
#include "smbios.h"

struct BootInfo 
{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	BMPImage* bmpImage;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;
	ACPI::RSDP2* rsdp;
	struct SMBiosHeader* SMBIOS;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo 
{
    PageTableManager* pageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);