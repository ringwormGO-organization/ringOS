#include "stdio.hpp"

namespace GUI
{
    namespace Renderer
    {
        typedef __builtin_va_list va_list;
        #define va_start(ap, X) __builtin_va_start(ap, X)
        #define va_arg(ap, type) __builtin_va_arg(ap, type)
        #define va_end(ap) __builtin_va_end(ap)

        void _putc(unsigned char c) { GlobalRenderer->PutChar((char)c); }

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
                            s = va_arg(ap, char*);
                            if (s == (void*)0)
                                s = (char*)"<NULL>";
                            GlobalRenderer->Print(to_string((int64_t) s));
                            continue;
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
                                        if ((u /= 16U) == false)
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
                    GlobalRenderer->CursorPosition.X = 0; 
                    GlobalRenderer->CursorPosition.Y += 16;
                    c++;
                    continue;
                }
                _putc((int)c);
            }
            va_end(ap);
        }
    }
}