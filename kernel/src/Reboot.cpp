#include "Reboot.hpp"

using namespace GUI::Text;

void Reboot()
{
    GlobalRenderer->Colour = RED;
    printf("Reboot function don't work!!");
    GlobalRenderer->Colour = DEFAULT;
}