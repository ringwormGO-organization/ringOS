#include "stdio.hpp"
#include "../BasicRenderer.hpp"

using namespace GUI::Renderer;

void putchar_(char character)
{
    GlobalRenderer->Print(char2str(character));
}