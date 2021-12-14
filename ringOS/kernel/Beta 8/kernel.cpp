#include <stdint.h>
#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"

struct BootInfo
{
	Framebuffer* framebuffer;
	PSF1_FONT* ps1_Font;
	void* mMap;
	uint64_t mMapSize;
	uint64_t mMapDescSize;

} ;

extern "C" void _start(BootInfo* bootInfo)
{
	BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->ps1_Font);
	newRenderer.Print("Welcome to ringOS!!");
	newRenderer.Print(" ");

    return ;
}