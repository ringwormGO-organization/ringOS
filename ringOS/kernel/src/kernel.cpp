#include "kernelUtil.h"
#include "memory/heap.hpp"
#include "scheduling/pit/pit.hpp"
#include "Window/Window.hpp"
#include "settings.h"

#define VERSION "v2.0.0 (stable)"

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
    GlobalRenderer->FullClear();

    //GUI initialization
    Init();

    GlobalRenderer->CursorPosition = {0, 0};

    #ifdef ENABLE_PRINTED_TEXT
    //Welcome
    GlobalRenderer->Colour = 0xff00ffff;
	GlobalRenderer->Next();
	printf("Welcome to ringOS!! Version: %s\n", VERSION);

    #ifdef RESOLUTION
	GlobalRenderer->Colour = 0xffffff00;

	//Resolution
    printf("Resolution: %ld x %ld", (long)ResoWidth, (long)ResoHeight);
    #endif

    GlobalRenderer->Colour = 0xffffffff;
    
    printf("\n\nClose application with ESC or F4.\n");
    printf("GUI has some bugs about mouse, but you can always use keyboard.\n");
    printf("Caluclator only support numbers to 9.\n\n");

    #ifdef RAM_INFO
        GlobalRenderer->Print(" ");
        GlobalRenderer->Colour = 0xffff0000;

        GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16};
        GlobalRenderer->Print("Free RAM: ");
        GlobalRenderer->Print(to_string(GlobalAllocator.GetFreeRAM() / 1024));
        GlobalRenderer->Print(" KB ");
        GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16};

        GlobalRenderer->Print("Used RAM: ");
        GlobalRenderer->Print(to_string(GlobalAllocator.GetUsedRAM() / 1024));
        GlobalRenderer->Print(" KB ");
        GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16};

        GlobalRenderer->Print("Reserved RAM: ");
        GlobalRenderer->Print(to_string(GlobalAllocator.GetReservedRAM() / 1024));
        GlobalRenderer->Print(" KB ");
        GlobalRenderer->CursorPosition = {0, GlobalRenderer->CursorPosition.Y + 16};
    #endif

    #ifdef RSDP_CHECK
        GlobalRenderer->Next();
        GlobalRenderer->Print(to_hstring((uint64_t)bootInfo->rsdp));
        GlobalRenderer->Next();
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 1));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 2));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 3));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 4));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 5));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 6));
        GlobalRenderer->PutChar(*((uint8_t*)bootInfo->rsdp + 7));
        GlobalRenderer->Next();
    #endif

    #ifdef SMBIOS_CHECK
        printf("SMBIOS Address: %x\n", bootInfo->SMBIOS);
        printf("SMBIOS Signature: %c%c%c%c\n", bootInfo->SMBIOS->EntryPointString[0], bootInfo->SMBIOS->EntryPointString[1], bootInfo->SMBIOS->EntryPointString[2], bootInfo->SMBIOS->EntryPointString[3]);

        SMBiosParse(bootInfo->SMBIOS);
    #endif

    #endif

    #ifdef MALLOC_EXAMPLE
        //malloc example 2
        void* test = malloc(0x100);
        free(test);

        WindowStuff->Width(ResoWidth);
        WindowStuff->Height(ResoHeight);
    #endif

    #ifdef PAGE_FAULT
        int* number = (int*)0x80000000000;
        *number = 2;
    #endif

    while(true) asm ("hlt");
}