#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"

extern "C" void _start(BootInfo* bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    //Clear
    PIT::Sleep(20000);
    GlobalRenderer->ClearColour = 0x00000000;
    GlobalRenderer->Clear();

    //taskbar
    uint64_t ResoWidth = (uint64_t)bootInfo->framebuffer->Width;
    uint64_t ResoHeight = (uint64_t)bootInfo->framebuffer->Height;

    if (ResoWidth == 1920 && ResoHeight == 1080)
    {
        GlobalRenderer->TaskBar(0xff00ffff, 1000);
        GlobalRenderer->Colour = 0x00ff0000;
        GlobalRenderer->CursorPosition = {0, 1000};
        GlobalRenderer->Print("START");

    }
    else if (ResoWidth == 1366 && ResoHeight == 768)
    {
        GlobalRenderer->TaskBar(0xff00ffff, 688);
        GlobalRenderer->Colour = 0x00ff0000;
        GlobalRenderer->CursorPosition = {0, 688};
        GlobalRenderer->Print("START");
    }
    else if (ResoWidth == 1024 && ResoHeight == 768)
    {
        GlobalRenderer->TaskBar(0xff00ffff, 688);
        GlobalRenderer->Colour = 0x00ff0000;
        GlobalRenderer->CursorPosition = {0, 688};
        GlobalRenderer->Print("START");
    }
    else if (ResoWidth == 2560 && ResoHeight == 1440)
    {
        GlobalRenderer->TaskBar(0xff00ffff, 1360);
        GlobalRenderer->Colour = 0x00ff0000;
        GlobalRenderer->CursorPosition = {0, 1360};
        GlobalRenderer->Print("START");
    }
    else if (ResoWidth == 4096 && ResoHeight == 2160)
    {
        GlobalRenderer->TaskBar(0xff00ffff, 2080);
        GlobalRenderer->Colour = 0x00ff0000;
        GlobalRenderer->CursorPosition = {0, 2080};
        GlobalRenderer->Print("START");
    }
    
    
    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->CursorPosition = {0, 0};
	GlobalRenderer->Print("Welcome to ringOS!!");
	GlobalRenderer->Print(" ");

	GlobalRenderer->Colour = 0xffffff00;
    GlobalRenderer->Next();

	//Resolution
    GlobalRenderer->Print("Resolution: ");
    GlobalRenderer->Print(to_string((uint64_t)ResoWidth));
    GlobalRenderer->Print(" x ");
    GlobalRenderer->Print(to_string((uint64_t)ResoHeight));

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    while(true)
    {
        asm ("hlt");
    }
}