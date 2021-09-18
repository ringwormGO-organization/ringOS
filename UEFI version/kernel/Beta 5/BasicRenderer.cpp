#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font)
{
    TargetFramebuffer = targetFramebuffer;
    PSF1_Font = psf1_Font;
    Colour = 0xff00ffff;
    CursorPosition = {200, 50};
}

void BasicRenderer::Print(const char* str)
{
	char* chr = (char*)str;
	while(*chr != 0){
		PutChar(*chr, CursorPosition.X, CursorPosition.Y);
		CursorPosition.X+=8;
		if (CursorPosition.X + 8 > TargetFramebuffer->Width)
		{
			CursorPosition.X = 0;
			CursorPosition.Y += 16;
		}
		chr++;
	}
}

void BasicRenderer::PutChar(char chr, unsigned int x0ff, unsigned int yOff)
{
	unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
	char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
	for (unsigned long y = yOff; y < yOff + 16; y++){
		for (unsigned long x = x0ff; x < x0ff + 8; x++){
			if ((*fontPtr & (0b10000000 >> (x - x0ff))) > 0){
				*(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Colour;
			}
		}
		fontPtr++;
	}
}