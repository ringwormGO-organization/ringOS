#include "TaskMgr.hpp"

TaskManager* GlobalTaskManager;

int lastTerminal = 1;

void TaskManager::Schedule(InterruptStack* registers)
{
    if(!isEnabled) return;

    memcpy(&tasks[currentTask].registers,(void*)registers,sizeof(InterruptStack));

    //Get next task
    do
    {
        currentTask++;
        if(taskNum <= currentTask) currentTask = 0;
    }
    while(tasks[currentTask].state == STATE_HALTED);  //load next task that isn't halted

    int kernelStack = registers->KernelRsp;
    memcpy((void*)registers,&tasks[currentTask].registers,sizeof(InterruptStack));
    registers->KernelRsp = kernelStack;
}

void TaskManager::AddTask(void* entry,void* stack,const char* name,uint8_t privilege,uint64_t executableSize)
{
    Task task;
    task.entryPoint = (uint64_t)entry;
    task.privilege = privilege;
    task.state = STATE_RUNNING;
    task.terminal = lastTerminal++;
    task.name = name;
    task.memoryUse = executableSize;

    memset(&task.registers,0,sizeof(InterruptStack));
    task.registers.rip = (uint64_t)entry;
    task.registers.rsp = (uint64_t)stack+(0x1000*8);
    task.registers.rflags = 0x202; //interrupts
    task.registers.cs = GDTInfoSelectors.UCode;
    task.registers.ss = GDTInfoSelectors.UData;

    int i = 0;
    while (tasks[i].state != STATE_HALTED) //find the first spot that's empty
        i++;

    if(i >= taskNum) taskNum = i+1;

    memcpy(&tasks[i],&task,sizeof(Task));

    g_PageTableManager.MapUserSpaceMemory(entry);
    g_PageTableManager.MapUserSpaceMemory(stack);
}

void TaskManager::ExitCurrentTask()
{
    tasks[currentTask].state = STATE_HALTED;
}