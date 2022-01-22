#include "cprint.h"

struct Framebuffer* cframebuffer;
struct PSF1_FONT* cpsf1_font;
struct Point cCursorPosition;

void putChar(unsigned int colour, char chr, unsigned int xOff, unsigned int yOff)
{
    unsigned int* pixPtr = (unsigned int*)cframebuffer->BaseAddress;
    char* fontPtr = cpsf1_font->glyphBuffer + (chr * cpsf1_font->psf1_Header->charsize);
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff; x < xOff+8; x++){
            if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
                    *(unsigned int*)(pixPtr + x + (y * cframebuffer->PixelsPerScanLine)) = colour;
                }

        }
        fontPtr++;
    }
}

void _putc(unsigned char c) { putChar(DEFAULT, (char)c, cCursorPosition.X, cCursorPosition.Y); }

void printf(const char* fmt, ...)
{
    const char digits[] = "0123456789abcdef";
    va_list ap;
    char buf[10];
    char* s;
    unsigned char u;
    int c, i, pad;

    va_start(ap, fmt);
    while ((c = *fmt++) != 0)
    {
        if (c == '%') 
        {
            c = *fmt++;
            if (c == 'l')
                c = *fmt++;
            switch (c)
            {
                case 'c':
                    _putc(va_arg(ap, int));
                    continue;
                case 's':
                    s = va_arg(ap, char*);
                    if (s == (void*)0)
                        s = (char*)"<NULL>";
                    for (; *s; s++)
                        _putc((int)*s);
                    continue;
                case '%':
                    _putc('%');
                    continue;
                case 'd':
                case 'i':
                    c = 'u';
                case 'u':
                case 'x':
                case 'X':
                    u = va_arg(ap, unsigned);
                    s = buf;
                    if (c == 'u') 
                    {
                        do
                            *s++ = digits[u % 10U];
                        while (u /= 10U);
                    } 
                    else
                    {
                        pad = 0;
                        for (i = 0; i < 8; i++) 
                        {
                            if (pad)
                                *s++ = '0';
                            else 
                            {
                                *s++ = digits[u % 16U];
                                if ((u /= 16U) == 0)
                                    pad = 1;
                            }
                        }
                    }

                while (--s >= buf)
                    _putc((int)*s);
                continue;
            }
        }
        else if(c == '\n')
        {
            cCursorPosition.X = 0; 
            cCursorPosition.Y += 16;
            c++;
            continue;
        }
        _putc((int)c);
    }
    va_end(ap);
}