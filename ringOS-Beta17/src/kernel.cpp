#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"
#include "test.h"

using namespace Renderer;
using namespace GUI;
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
    GlobalRenderer->TaskBar();
    GlobalRenderer->Colour = 0x00ff0000;
    GlobalRenderer->CursorPosition = {0, (long) ResoHeight - 80};
    GlobalRenderer->Print("START");

    GlobalRenderer->CursorPosition = {0, 0};

    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->Next();
	GlobalRenderer->printf("Welcome to ringOS!!\n");

	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    GlobalRenderer->printf("Resolution: ");
    GlobalRenderer->printf("%d", ResoWidth);
    GlobalRenderer->printf(" x ");
    GlobalRenderer->printf("%d", ResoHeight);

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->Next();
    GlobalRenderer->Next();

    //malloc example 2
    void* test = malloc(0x100);
    free(test);

    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    while(true) asm ("hlt");
}