
#include "panic.hpp"

void Panic(const char* panicMessage)
{
    e9_printf(CLEAR);

    e9_printf(ANSI_COLOR_RED);
    e9_printf(":( Kernel Panic");
    e9_printf(ANSI_COLOR_RESET);

    e9_printf("Restart your computer!!");

    e9_printf("Error name: %s\n", panicMessage);
}

void Panic(const char* panicMessage, int code)
{
    e9_printf(CLEAR);

    e9_printf(ANSI_COLOR_RED);
    e9_printf(":( Kernel Panic");
    e9_printf(ANSI_COLOR_RESET);
    
    e9_printf("Restart your computer!!");

    e9_printf("Error name: %s | Error code: %d\n", panicMessage, code);
}