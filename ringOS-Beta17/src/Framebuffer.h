#pragma once
#include <stddef.h>

struct Framebuffer{
	unsigned int* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};