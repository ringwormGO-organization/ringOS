#include "userspace.h"

#define CurrentTask GlobalTaskManager->tasks[GlobalTaskManager->currentTask]

void SysConsoleWrite(char text)
{
    printf("%s, %c", CurrentTask.terminal,"%c",text);
}

void SysSerialWrite(char text)
{
    SerialWrite(text);
}

void Exit(uint64_t code)
{
    printf("%s", CurrentTask.terminal,"\nProgram exit code: %u\n", code);
    GlobalTaskManager->ExitCurrentTask();
}

//                                  RDX            RDI             RSI                                  R8             R9
uint64_t SyscallHandler(uint64_t syscall, uint64_t arg1, uint64_t arg2, uint64_t doNotModify, uint64_t arg3, uint64_t arg4)
{
    switch (syscall)
    {
        case SYSCALL_WRITE:
            if(arg2 == SOUT) SysSerialWrite((char)arg1); //write on serial
            else SysConsoleWrite((char)arg1); //write on tty
            break;
        case SYSCALL_EXIT:
            Exit(arg1); //exit
            break;
        case SYSCALL_OPEN:
        {
            break;
        }
        case SYSCALL_ALLOCATEMEMORY:
        {
            if(!arg1) return 0;
            CurrentTask.memoryUse += arg1 * 4096; //it allocates pages, each being 4 kilobytes
            void* mem = GlobalAllocator.RequestPages(arg1); //request pages
            for(int i = 0; i<=4096*arg1; i++)
                g_PageTableManager.MapUserSpaceMemory((void*)((uint64_t)mem+i));
            return (uint64_t)mem; //return pointer
            break;
        }
        case SYSCALL_READ:
        {
            break;
        }
        case SYSCALL_GETTERMINALOUTPUT:
            break;
        case SYSCALL_GETPROCESSTERMINAL:
            return CurrentTask.terminal; //get terminal
            break;
        case SYSCALL_GETPIDBYNAME:
        {
            for(int i = 0; i<1024; i++)
            {
                if(memcmp((const void*)arg1,GlobalTaskManager->tasks[i].name,strlen(GlobalTaskManager->tasks[i].name))==0) //check every task's name
                    return i;
            }
            return 0xFFFFFFFFFFFFFFFF;
            break;
        }
        case SYSCALL_GETPID:
            return GlobalTaskManager->currentTask; //get pid
            break;
        case SYSCALL_GETTERMINALBYPID:
            return GlobalTaskManager->tasks[arg1].terminal; //get terminal of a pid
            break;
        default:
            return ERROR_UNKNOWN_SYSCALL;
            break;
    }
    return 512;
}