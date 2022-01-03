#include "kernelUtil.h"
#include "memory/heap.h"
#include "scheduling/pit/pit.h"
#include "Window/Window.h"

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

    //BMP picture loading
    if (bootInfo->bmpImage->height != bootInfo->framebuffer->Height || bootInfo->bmpImage->width != bootInfo->framebuffer->Width)
    {
        uint32_t previousColour = GlobalRenderer->Colour;
        GlobalRenderer->Colour = 0xffff0000;
        GlobalRenderer->Print("BMP image is not the same resolution as the screen resolution!");
        GlobalRenderer->Next();
        GlobalRenderer->Colour= previousColour;
    }

    // Bottom-up rendering
    for (unsigned int y = 0; y < bootInfo->bmpImage->height; ++y)
    {
        for (unsigned int x = 0; x < bootInfo->bmpImage->width; ++x)
        {
            unsigned int* framebufferPtr = bootInfo->framebuffer->BaseAddress + bootInfo->bmpImage->width * y + x;
            unsigned int* pixPtr = bootInfo->bmpImage->bitmapBuffer + (bootInfo->bmpImage->height - 1 - y) * bootInfo->bmpImage->width + x;
            *framebufferPtr = *pixPtr;
        }
    }

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
	GlobalRenderer->Print("Welcome to ringOS!!");
	GlobalRenderer->Print(" ");

	GlobalRenderer->Colour = 0xffffff00;
    GlobalRenderer->Next();

	//Resolution
    GlobalRenderer->Print("Reso\nlution: ");
    GlobalRenderer->Print(to_string((uint64_t)ResoWidth));
    GlobalRenderer->Print(" x ");
    GlobalRenderer->Print(to_string((uint64_t)ResoHeight));

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    //Terminal
    GlobalRenderer->Print("ringOS> ");

    while(true)
    {
        asm ("hlt");
    }
}