#include <stdint.h>
#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "Framebuffer.h"
#include "efiMemory.h"
#include "memory.h"
#include "Bitmap.h"

struct BootInfo
{
	Framebuffer* framebuffer;
	PSF1_FONT* ps1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;

	void* BaseAddress;
	size_t BufferSize; 
	
	unsigned int Width; 
	unsigned int Height; 
	unsigned int PixelsPerScanLine;

	uint64_t mMapSize;
	uint64_t mMapDescSize;

	uint64_t mReso;
	uint64_t mResoSize;
	uint64_t mResoDescSize;

} ;

uint8_t testBuffer[20];

extern "C" void _start(BootInfo* bootInfo)
{
	BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->ps1_Font);

	//Welcome
	newRenderer.CursorPosition = {0, 0};
	newRenderer.Print("Welcome to ringOS!!");
	newRenderer.Print(" ");

	//Basic system info
	newRenderer.Colour = 0xffffff00;

	newRenderer.CursorPosition = {0, 16};
	newRenderer.Print("Basic System Info:");
	newRenderer.Print(" ");

	newRenderer.Print("Width: ");
	newRenderer.Print(to_string((uint64_t)bootInfo->framebuffer->Width));
	newRenderer.Print(" | ");

	newRenderer.Print("Height: ");
	newRenderer.Print(to_string((uint64_t)bootInfo->framebuffer->Height));
	newRenderer.Print(" | ");

	newRenderer.Print("PixelsPerScanLine: ");
	newRenderer.Print(to_string((uint64_t)bootInfo->framebuffer->PixelsPerScanLine));
	newRenderer.Print(" | ");

	//Page Frame Allocator
	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;



	/*
	//EFI MAP
	newRenderer.Print(to_string(GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize)));

	for (int i = 0; i < mMapEntries; i++)
	{
		EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));
		newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
		newRenderer.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
		newRenderer.Colour = 0xffff00ff;
		newRenderer.Print(" ");
		newRenderer.Print(to_string(desc->numPages * 4096 / 1024));
		newRenderer.Print(" KB");
		newRenderer.Colour = 0xff00ffff;
	}
	*/

    return ;
}
