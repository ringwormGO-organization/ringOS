#include "shutdown.hpp"

using namespace GUI;

void Shutdown()
{
    UnInit();

    outw(0x604, 0x2000); //Newer versions of Qemu
    outw(0xB004, 0x2000); //Bochs, and older versions of Qemu(than 2.0)
    outw(0x4004, 0x3400); //Virtual Box
}