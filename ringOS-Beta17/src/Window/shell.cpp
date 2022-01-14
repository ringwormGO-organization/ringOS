#include "shell.hpp"

Shell* ShellStuff;

void Shell::ShellInit()
{
    BasicStuff->Square(300, 300, 200, 200, GRAY);

    GlobalRenderer->CursorPosition2 = {shellx + 20, shelly + 20};
    GlobalRenderer->Print("ringOS> ", 2);
}