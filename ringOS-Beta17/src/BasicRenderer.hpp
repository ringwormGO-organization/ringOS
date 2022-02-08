#pragma once

#include <stdint.h>

#include "math.h"
#include "BMPImageFile.h"
#include "Framebuffer.h"
#include "simpleFonts.h"
#include "tga/tga.h"
#include "cstr.hpp"
#include "IO.hpp"
#include "library/stdio.hpp"
#include "Window/Window.hpp"

namespace GUI
{
    namespace Renderer
    {
        class BasicRenderer
        {
            public:
                BasicRenderer(Framebuffer* targetFramebuffer, PSF1_FONT* psf1_Font, BMPImage* bmpImage);
                Point CursorPosition;
                Point CursorPosition2;
                Framebuffer* TargetFramebuffer;
                PSF1_FONT* PSF1_Font;
                BMPImage* BMPimage;
                uint32_t MouseCursorBuffer[16 * 16];
                uint32_t MouseCursorBufferAfter[16 * 16];
                unsigned int Colour;
                unsigned int ClearColour;
                void Print(const char* str);
                void Print(const char* str, int type);
                void PutChar(char chr, unsigned int xOff, unsigned int yOff);
                void PutChar(char chr);
                void PutChar2(char chr);
                void PutPix(uint32_t x, uint32_t y, uint32_t colour);
                uint32_t GetPix(uint32_t x, uint32_t y);
                void ClearChar();
                void ClearChar(int type);
                void Clear();
                void FullClear();
                void Next();
                void Next(int type);
                void DrawOverlayMouseCursor(uint8_t* cursor, Point position, uint32_t colour);
                void ClearMouseCursor(uint8_t* cursor, Point position);
                bool MouseDrawn;
                void TaskBar();
                int BMPPicture();

            private:
                void ClearChar2();
        };

        extern BasicRenderer* GlobalRenderer;
    }
}