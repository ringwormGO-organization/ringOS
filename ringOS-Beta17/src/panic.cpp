#include "panic.hpp"
#include "BasicRenderer.hpp"
#include "IO.hpp"
#include "Reboot.hpp"
#include "shutdown.hpp"

#include "BasicRenderer.hpp"
#include "paging/PageFrameAllocator.hpp"

using namespace Renderer;

void Panic(const char* panicMessage)
{
    GlobalRenderer->ClearColour = 0xff00ffff;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    GlobalRenderer->Print(":( Kernel Panic", 1);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Restart your computer!!", 1);


    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);

    MorePanic();
}

void Panic(const char* panicMessage, unsigned long int code)
{
    GlobalRenderer->ClearColour = 0xff00ffff;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    GlobalRenderer->Print(":( Kernel Panic", 1);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Restart your computer!!", 1);

    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Error code: ");
    GlobalRenderer->Print(to_string((long int)code));

    MorePanic();
}

void MorePanic()
{
    GlobalRenderer->Next();
    GlobalRenderer->Next();


    GlobalRenderer->Print("Free RAM: ", 1);
    GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM() / 1024), 1);
    GlobalRenderer->Print(" KB ", 1);

    GlobalRenderer->Next();

    GlobalRenderer->Print("Used RAM: ", 1);
    GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM() / 1024), 1);
    GlobalRenderer->Print(" KB ", 1);

    GlobalRenderer->Next();

    GlobalRenderer->Print("Reserved RAM: ", 1);
    GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM() / 1024), 1);
    GlobalRenderer->Print(" KB ", 1);
}