#include "bootparam.h"
#include "font.hpp"

bootparam_t *bootp;

/* Scalable Screen Font (https://gitlab.com/bztsrc/scalable-font2) */
typedef struct {
    unsigned char  magic[4];
    unsigned int   size;
    unsigned char  type;
    unsigned char  features;
    unsigned char  width;
    unsigned char  height;
    unsigned char  baseline;
    unsigned char  underline;
    unsigned short fragments_offs;
    unsigned int   characters_offs;
    unsigned int   ligature_offs;
    unsigned int   kerning_offs;
    unsigned int   cmap_offs;
} __attribute__((packed)) ssfn_font_t;

/* font to be used */
ssfn_font_t *font = (ssfn_font_t*)&font_data;

/**
 * Display string using a bitmap font without the SSFN library
 */
void printString(int x, int y, const char *s)
{
    unsigned char *ptr, *chr, *frg;
    unsigned int c;
    unsigned long long int o, p;
    int i, j, k, l, m, n;
    while(*s) {
        if((*s & 128) != 0) {
            if(!(*s & 32)) { c = ((*s & 0x1F)<<6)|(*(s+1) & 0x3F); s += 1; } else
            if(!(*s & 16)) { c = ((*s & 0xF)<<12)|((*(s+1) & 0x3F)<<6)|(*(s+2) & 0x3F); s += 2; } else
            if(!(*s & 8)) { c = ((*s & 0x7)<<18)|((*(s+1) & 0x3F)<<12)|((*(s+2) & 0x3F)<<6)|(*(s+3) & 0x3F); s += 3; }
            else c = 0;
        } else c = *s;
        s++;
        if(c == '\r') { x = 0; continue; } else
        if(c == '\n') { x = 0; y += font->height; continue; }
        for(ptr = (unsigned char*)font + font->characters_offs, chr = 0, i = 0; i < 0x110000; i++) {
            if(ptr[0] == 0xFF) { i += 65535; ptr++; }
            else if((ptr[0] & 0xC0) == 0xC0) { j = (((ptr[0] & 0x3F) << 8) | ptr[1]); i += j; ptr += 2; }
            else if((ptr[0] & 0xC0) == 0x80) { j = (ptr[0] & 0x3F); i += j; ptr++; }
            else { if((unsigned int)i == c) { chr = ptr; break; } ptr += 6 + ptr[1] * (ptr[0] & 0x40 ? 6 : 5); }
        }
        if(!chr) continue;
        ptr = chr + 6; o = (unsigned long long int)bootp->framebuffer + y * bootp->pitch + x * 4;
        for(i = n = 0; i < chr[1]; i++, ptr += chr[0] & 0x40 ? 6 : 5) {
            if(ptr[0] == 255 && ptr[1] == 255) continue;
            frg = (unsigned char*)font + (chr[0] & 0x40 ? ((ptr[5] << 24) | (ptr[4] << 16) | (ptr[3] << 8) | ptr[2]) :
                ((ptr[4] << 16) | (ptr[3] << 8) | ptr[2]));
            if((frg[0] & 0xE0) != 0x80) continue;
            o += (int)(ptr[1] - n) * bootp->pitch; n = ptr[1];
            k = ((frg[0] & 0x1F) + 1) << 3; j = frg[1] + 1; frg += 2;
            for(m = 1; j; j--, n++, o += bootp->pitch)
                for(p = o, l = 0; l < k; l++, p += 4, m <<= 1) {
                    if(m > 0x80) { frg++; m = 1; }
                    if(*frg & m) *((unsigned int*)p) = 0xFFFFFF;
                }
        }
        x += chr[4]+1; y += chr[5];
    }
}

/**
 * Example "kernel"
 */
extern "C" void _start(bootparam_t *bootpar)
{
    int i;
    bootp = bootpar;
    for(i = 0; i < bootp->width * bootp->height; i++)
        bootp->framebuffer[i] = 0x000008;

    printString(10, 10, "Hello from \"kernel\". I got arguments: ");
    for(i = 0; i < bootp->argc; i++)
        printString(20, 10 + (i + 1) * font->height, bootp->argv[i]);


    /* there's nowhere to return to, hang */
    while(true)
    {
        asm ("hlt");
    }
}