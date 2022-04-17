#include "stdio.hpp"
#include "../BasicRenderer.hpp"

using namespace GUI::Text;

void putchar_(char character)
{
    GlobalRenderer->Print(char2str(character));
}