#include "kernelUtil.h"


extern "C" void _start(BootInfo* bootInfo){

    KernelInfo kernelInfo = InitializeKernel(bootInfo);
    PageTableManager* pageTableManager = kernelInfo.pageTableManager;
    BasicRenderer newRenderer = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font);


    //Welcome
    newRenderer.Colour = 0xff00ffff;
	newRenderer.CursorPosition = {0, 0};
	newRenderer.Print("Welcome to ringOS!!");
	newRenderer.Print(" ");

	newRenderer.Colour = 0xffffff00;
    newRenderer.CursorPosition = {0, 16};

	//Resolution
    newRenderer.Print("Resolution: ");
    newRenderer.Print(to_string((uint64_t)bootInfo->framebuffer->Width));
    newRenderer.Print(" x ");
    newRenderer.Print(to_string((uint64_t)bootInfo->framebuffer->Height));

    newRenderer.Colour = 0xffffffff;
    newRenderer.CursorPosition = {0, 32};


    while(true);
}