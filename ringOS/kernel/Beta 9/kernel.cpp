#include <stdint.h>
#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"
#include "Framebuffer.h"
#include "efiMemory.h"
#include "memory.h"

struct BootInfo
{
	Framebuffer* framebuffer;
	PSF1_FONT* ps1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;

	uint64_t mReso;
	uint64_t mResoSize;
	uint64_t mResoDescSize;

} ;


/*/
void Info()
{

	Framebuffer->BaseAddress = (void*)BaseAddress;
	Framebuffer->BufferSize = BufferSize;
	Framebuffer->Width = Height;
	Framebuffer->Height = Width;
	Framebuffer->PixelsPerScanLine = PixelsPerScanLine;
}
/*/

extern "C" void _start(BootInfo* bootInfo)
{
	BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->ps1_Font);

	newRenderer.CursorPosition = {0, 0};
	newRenderer.Print("Welcome to ringOS!!");

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

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


    return ;
}