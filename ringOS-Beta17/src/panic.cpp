#include "panic.hpp"
#include "BasicRenderer.hpp"
#include "paging/PageFrameAllocator.hpp"
#include "settings.h"

#include "shutdown.hpp"
#include "Reboot.hpp"

using namespace GUI::Renderer;

void Panic(const char* panicMessage)
{
    GlobalRenderer->ClearColour = PANIC_COLOR;
    GlobalRenderer->FullClear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    GlobalRenderer->Print(":( Kernel Panic");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Restart your computer!!");


    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);

    MorePanic();
}

void Panic(const char* panicMessage, unsigned long int code)
{
    GlobalRenderer->ClearColour = PANIC_COLOR;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    printf(":( Kernel Panic\nRestart your computer!!\n\n");

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Error code: ");
    GlobalRenderer->Print(to_string((long int)code));

    MorePanic();
}

void MorePanic()
{
#ifdef PRINT_RAM_INFO
    printf("\n\nFree RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
    GlobalRenderer->Print(" KB ", 1);

    GlobalRenderer->Next();

    GlobalRenderer->Print("Used RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
    GlobalRenderer->Print(" KB ");

    GlobalRenderer->Next();

    GlobalRenderer->Print("Reserved RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
    GlobalRenderer->Print(" KB ");
#endif

#ifdef SHUTDOWN
    Shutdown();
#endif

#ifdef REBOOT
    Reboot();
#endif
}