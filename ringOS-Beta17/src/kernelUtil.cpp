#include "kernelUtil.h"
#include "gdt/gdt.h"
#include "interrupts/IDT.hpp"
#include "interrupts/interrupts.hpp"
#include "IO.hpp"
#include "memory/heap.hpp"
#include "elf/Load.hpp"
#include "filesystem/llfs.hpp"
#include "filesystem/vfs.hpp"
#include "UserMode/TaskMgr.hpp"
#include "UserMode/userspace.h"

using namespace GUI::Renderer;

KernelInfo kernelInfo; 

void PrepareMemory(BootInfo* bootInfo)
{
    uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    memset(PML4, 0, 0x1000);

    g_PageTableManager = PageTableManager(PML4);

    for (uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescSize); t+= 0x1000)
    {
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096)
    {
        g_PageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.pageTableManager = &g_PageTableManager;
}

IDTR idtr;
void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector)
{

    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts()
{
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();

    SetIDTGate((void*)PageFault_Handler, 0xE, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)DoubleFault_Handler, 0x8, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)GPFault_Handler, 0xD, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)KeyboardInt_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)MouseInt_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);
    SetIDTGate((void*)PITInt_Handler, 0x20, IDT_TA_InterruptGate, 0x08);
 
    asm ("lidt %0" : : "m" (idtr));

    RemapPIC();
}

void PrepareACPI(BootInfo* bootInfo)
{
    ACPI::SDTHeader* xsdt = (ACPI::SDTHeader*)(bootInfo->rsdp->XSDTAddress);
    
    ACPI::MCFGHeader* mcfg = (ACPI::MCFGHeader*)ACPI::FindTable(xsdt, (char*)"MCFG");

    PCI::EnumeratePCI(mcfg);
}

extern "C" void IdleTask();

void* GenerateUserspaceStack()
{
    void* Stack = GlobalAllocator.RequestPages(8);
    uint64_t StackSize = 0x1000*8; //32k
    for (uint64_t t = (uint64_t)Stack; t < (uint64_t)Stack + StackSize; t += 4096)
    {
        g_PageTableManager.MapUserSpaceMemory((void*)t);
    }
    return Stack;
}

void InitUserMode(BootInfo* bootInfo)
{
    //llfs
    uint64_t fssize = LLFSGetFileSystemSize(bootInfo->RAMFS);
    LLFSSource = (LLFSHeader*)GlobalAllocator.RequestPages(fssize/4096+1);
    memcpy(LLFSSource, bootInfo->RAMFS, fssize);
    LLFSMap(LLFSSource); //map as user memory

    VFSSource = VFS_SOURCE_RAMFS;

    //and lock the pages
    GlobalAllocator.LockPages(LLFSSource,fssize/4096+1);

    //init filesystem
    VFSInit();

    //map files from llfs into the vfs
    LLFSEntry* firstEntry = (LLFSEntry*)((uint64_t)LLFSSource+sizeof(LLFSHeader));
    uint64_t fsize = sizeof(LLFSHeader);
    for(int i = 0; i<LLFSSource->Entries; i++)
    {
        FileDescriptor descriptor;
        memcpy(descriptor.path,firstEntry->Filename,368);
        descriptor.source = VFS_SOURCE_RAMFS;
        VFSAdd(descriptor);
        firstEntry = (LLFSEntry*)((uint64_t)firstEntry+sizeof(LLFSEntry)+firstEntry->FileSize);
    }

    printf("VFS total entries: %u\n",VFSTotalEntries);

    //init taskmanager
    TaskManager tmgr;
    GlobalTaskManager = &tmgr;

    void* lastAddr = malloc(1);
    void* offset = malloc(0x0000100000200000-(uint64_t)lastAddr-sizeof(HeapSegHdr)*3);
    void* address = malloc(1*1024*1024); //1 mb
    //userspace
    void* moldInit = LoadELFExecutable("/minit.melf",false);

    if(moldInit == (void*)0)
    {
        printf("File is missing or corrupted.");
    }

    g_PageTableManager.MapUserSpaceMemory((void*)IdleTask);
    GlobalTaskManager->AddTask((void*)IdleTask, GenerateUserspaceStack(), "Idle Task", TASK_SYSTEM,0);
    GlobalTaskManager->AddTask(moldInit, GenerateUserspaceStack(),"/minit.melf",TASK_USER,VFSSizeFile(VFSOpenFile("/minit.melf")));
    //jump in the userspace
    GlobalTaskManager->isEnabled = 1;
    RunInUserspace((void*)IdleTask,GenerateUserspaceStack());
}

BasicRenderer r = BasicRenderer(NULL, NULL, NULL);
KernelInfo InitializeKernel(BootInfo* bootInfo)
{
    r = BasicRenderer(bootInfo->framebuffer, bootInfo->psf1_Font, bootInfo->bmpImage);
    GlobalRenderer = &r;

    GDTInit();

    PrepareMemory(bootInfo);

    //memset(bootInfo->framebuffer->BaseAddress, 0, bootInfo->framebuffer->BufferSize);

    InitializeHeap((void*)0x0000100000000000, 0x20);

    PrepareInterrupts();

    InitPS2Mouse();

    PrepareACPI(bootInfo);

    outb(PIC1_DATA, 0b11111000);
    outb(PIC2_DATA, 0b11101111);

    asm ("sti");

    return kernelInfo;
}