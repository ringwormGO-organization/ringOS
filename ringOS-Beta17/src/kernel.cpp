#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"
#include "shell/shell.hpp"

extern "C" void _start(BootInfo* bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    uint64_t ResoWidth = (uint64_t)bootInfo->framebuffer->Width;
    uint64_t ResoHeight = (uint64_t)bootInfo->framebuffer->Height;

    //for Start Menu
    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    //Clear
    PIT::Sleep(20000);
    GlobalRenderer->ClearColour = 0x00000000;
    GlobalRenderer->Clear();

    //taskbar
    switch (ResoWidth | ResoHeight)
    {
        case 1920 | 1080:
            GlobalRenderer->TaskBar(0xff00ffff, 1000);
            GlobalRenderer->Colour = 0x00ff0000;
            GlobalRenderer->CursorPosition = {0, 1000};
            GlobalRenderer->Print("START");
            break;
        
        case 1366 | 768:
            GlobalRenderer->TaskBar(0xff00ffff, 688);
            GlobalRenderer->Colour = 0x00ff0000;
            GlobalRenderer->CursorPosition = {0, 688};
            GlobalRenderer->Print("START");
            break;

        case 1024 | 768:
            GlobalRenderer->TaskBar(0xff00ffff, 688);
            GlobalRenderer->Colour = 0x00ff0000;
            GlobalRenderer->CursorPosition = {0, 688};
            GlobalRenderer->Print("START");
            break;

        default:
            break;
    }

    GlobalRenderer->CursorPosition = {0, 0};

    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->Next();
	GlobalRenderer->Print("Welcome to ringOS!!\n", 1);

	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    GlobalRenderer->Print("Resolution: ", 1);
    GlobalRenderer->Print(to_string((uint64_t)ResoWidth), 1);
    GlobalRenderer->Print(" x ", 1);
    GlobalRenderer->Print(to_string((uint64_t)ResoHeight), 1);

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    shell();

    while (true)
    {
        asm ("hlt");
    }
}