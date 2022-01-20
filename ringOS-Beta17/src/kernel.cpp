#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"

using namespace Renderer;
using namespace PIT;

extern "C" void _start(BootInfo* bootInfo)
{
    KernelInfo kernelInfo = InitializeKernel(bootInfo);

    uint64_t ResoWidth = (uint64_t)bootInfo->framebuffer->Width;
    uint64_t ResoHeight = (uint64_t)bootInfo->framebuffer->Height;


    //for Start Menu
    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    //Clear
    Sleep(20000);
    GlobalRenderer->ClearColour = 0x00000000;
    GlobalRenderer->Clear();

    GlobalRenderer->BMPPicture();

    //taskbar
    switch (ResoWidth | ResoHeight)
    {
        case 1920 | 1080:
            GlobalRenderer->TaskBar();
            GlobalRenderer->Colour = 0x00ff0000;
            GlobalRenderer->CursorPosition = {0, 1000};
            GlobalRenderer->Print("START");
            break;
        
        case 1366 | 768:
            GlobalRenderer->TaskBar();
            GlobalRenderer->Colour = 0x00ff0000;
            GlobalRenderer->CursorPosition = {0, 688};
            GlobalRenderer->Print("START");
            break;

        case 1024 | 768:
            GlobalRenderer->TaskBar();
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
	GlobalRenderer->printf("Welcome to ringOS!!\n");

	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    GlobalRenderer->printf("Resolution: ");
    GlobalRenderer->printf(to_string((uint64_t)ResoWidth));
    GlobalRenderer->printf(" x ");
    GlobalRenderer->printf(to_string((uint64_t)ResoHeight));

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    //malloc example 2
    void* test = malloc(0x100);
    free(test);

    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    while (true)
    {
        asm ("hlt");
    }
}