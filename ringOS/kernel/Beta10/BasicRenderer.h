#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simpleFonts.h"


class BasicRenderer{
    public:
    BasicRenderer(Framebuffer* TargetFramebuffer, PSF1_FONT* psf1_Font);
    Point CursorPosition;
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;

    void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
    unsigned int Colour;
    
    void Print(const char* str);
    void PutChar(char chr, unsigned int x0ff, unsigned int yOff);
};