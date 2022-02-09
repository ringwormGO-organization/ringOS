#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"

#define VERSION "Beta17"

using namespace GUI;
using namespace GUI::Renderer;
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

    //GUI initialization
    Init();

    //User Mode initialization
    //InitUserMode(bootInfo);

    GlobalRenderer->CursorPosition = {0, 0};

    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->Next();
	printf("Welcome to ringOS!! Version: %s\n", VERSION);

	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    printf("Resolution: %ld x %ld", (long)ResoWidth, (long)ResoHeight);

    GlobalRenderer->Colour = 0xffffffff;
    
    printf("\n\nClose application with ESC or F4.\n");
    printf("GUI has some bugs about mouse, but you can always use keyboard.\n");
    printf("Caluclator only support numbers to 9.\n\n");

    //malloc example 2
    void* test = malloc(0x100);
    free(test);

    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    while(true) asm ("hlt");
}