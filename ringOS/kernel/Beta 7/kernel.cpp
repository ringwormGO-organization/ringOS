#include <stdint.h>
#include <stddef.h>
#include "BasicRenderer.h"
#include "cstr.h"

extern "C" void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font)
{
	BasicRenderer newRenderer = BasicRenderer(framebuffer, psf1_font);
	newRenderer.Print("Welcome to ringOS!!");
	newRenderer.Print(" ");

	newRenderer.CursorPosition = {0, 20};
	newRenderer.Print("Few numbers for testing:");

	newRenderer.CursorPosition = {0, 40};
	newRenderer.Print(to_string((uint64_t)1234567890));

	newRenderer.CursorPosition = {0, 60};
	newRenderer.Print(to_string((int64_t)-123456789));

	newRenderer.CursorPosition = {0, 80};
	newRenderer.Print(to_string((double)123.4567890, 2)); //Add ',2' on end for decimal numbers

	newRenderer.CursorPosition = {0, 100};
	newRenderer.Print(to_string((double)-123.45, 2)); //Add ',2' on end for decimal numbers

	//Hexadecimal values//
	//newRenderer.Print(to_hstring((uint64_t)0xF0));
    //newRenderer.CursorPosition = {5, newRenderer.CursorPosition.Y + 16};
    //newRenderer.Print(to_hstring((uint32_t)0xF0));
    //newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 160};
    //newRenderer.Print(to_hstring((uint16_t)0xF0));
    //newRenderer.CursorPosition = {0, newRenderer.CursorPosition.Y + 16};
    //newRenderer.Print(to_hstring((uint8_t)0xF0));

    return ;
}