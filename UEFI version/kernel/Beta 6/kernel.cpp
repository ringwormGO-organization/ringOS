#include <stdint.h>
#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) 
{
	BasicRenderer newRenderer = BasicRenderer(framebuffer, psf1_font);
	newRenderer.Print("Welcome to ringOS!!");
	newRenderer.Print(" ");
	newRenderer.Print("Few numbers for testing:");
	newRenderer.Print(" ");
	newRenderer.Print(to_string((uint64_t)1234567890));
	newRenderer.Print(" ");
	newRenderer.Print(to_string((int64_t)-123456789));

    return ;
}