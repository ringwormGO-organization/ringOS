#include "Reboot.hpp"

using namespace GUI::Renderer;

void Reboot()
{
    GlobalRenderer->Colour = RED;
    printf("Reboot function don't work!!");
    GlobalRenderer->Colour = DEFAULT;
}