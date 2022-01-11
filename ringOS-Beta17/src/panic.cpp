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

    GlobalRenderer->Print(":( Kernel Panic", 1);
    GlobalRenderer->Next();
    GlobalRenderer->Print("Restart your computer!!", 1);


    GlobalRenderer->Next();
    GlobalRenderer->Next();

    GlobalRenderer->Print(panicMessage, 1);

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