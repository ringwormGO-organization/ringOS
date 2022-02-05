#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"
#include "Serial.hpp"
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

    //GUI initialization
    Init();

    GlobalRenderer->CursorPosition = {0, 0};

    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->Next();
	printf("Welcome to ringOS!!\n");

	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    printf("Resolution: %d x %d", ResoWidth, ResoHeight);

    GlobalRenderer->Colour = 0xffffffff;
    
    printf("\n\nClose application with ESC or Alt+F4\n\n");

    //malloc example 2
    void* test = malloc(0x100);
    free(test);

    WindowStuff->Width(ResoWidth);
    WindowStuff->Height(ResoHeight);

    while(true) asm ("hlt");
}