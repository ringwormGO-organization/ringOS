#include <stddef.h>
#include "BasicRenderer.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font) 
{
	BasicRenderer newRenderer = BasicRenderer(framebuffer, psf1_font);
	newRenderer.Print("Welcome to ringOS!!");

    return ;
}