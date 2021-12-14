#include "kernelUtil.h"

extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;

   //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->CursorPosition = {0, 0};
	GlobalRenderer->Print("Welcome to ringOS!!");
	GlobalRenderer->Print(" ");

    GlobalRenderer->Colour = 0xffffff00;
    GlobalRenderer->CursorPosition = {0, 16};

	//Resolution
    GlobalRenderer->Print("Resolution: ");
    GlobalRenderer->Print(to_string((uint64_t)bootInfo->framebuffer->Width));
    GlobalRenderer->Print(" x ");
    GlobalRenderer->Print(to_string((uint64_t)bootInfo->framebuffer->Height));

    GlobalRenderer->Colour = 0xffffffff;
    GlobalRenderer->CursorPosition = {0, 32};

    while(true);
}