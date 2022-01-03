#include "panic.h"
#include "BasicRenderer.h"
#include "IO.h"
#include "scheduling/pit/pit.h"
#include "Reboot.h"
#include "shutdown.h"

#include "BasicRenderer.h"
#include "paging/PageFrameAllocator.h"

void Panic(const char* panicMessage)
{
    GlobalRenderer->ClearColour = 0xff00ffff;
    GlobalRenderer->Clear();

    GlobalRenderer->CursorPosition = {0, 0};

    GlobalRenderer->Colour = 0;

    GlobalRenderer->Print(":( Kernel Panic");
    GlobalRenderer->Next();
    GlobalRenderer->Print("Restart your computer!!");


    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage);

    GlobalRenderer->Next();
    GlobalRenderer->Next();


    GlobalRenderer->Print("Free RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
    GlobalRenderer->Print(" KB ");

    GlobalRenderer->Next();

    GlobalRenderer->Print("Used RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
    GlobalRenderer->Print(" KB ");

    GlobalRenderer->Next();

    GlobalRenderer->Print("Reserved RAM: ");
    GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
    GlobalRenderer->Print(" KB ");
}