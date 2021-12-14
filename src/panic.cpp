#include "panic.h"
#include "BasicRenderer.h"
#include "IO.h"
#include "scheduling/pit/pit.h"
#include "Reboot.h"

void Panic(const char* panicMessage){
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


    PIT::Sleep(20000);
    Reboot();
}