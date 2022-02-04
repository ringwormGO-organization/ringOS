#include "shell.hpp"

Shell* ShellStuff;

using namespace Renderer;
using namespace GUI;

void Shell::ShellInit()
{
    BasicStuff->Square(300, 300, 200, 200, GRAY);

    GlobalRenderer->CursorPosition2 = {shellx + 20, shelly + 50};
    printf("ringOS> ");
}

void Shell::Command()
{
	while (1)
	{
		printf("\nUser> ");

		char* ch; // = readStr();

		if(strEql(ch, "cmd"))
		{
			printf("\nYou are already in CMD mode\n");
		}
		else if(strEql(ch, "help"))
		{
			printf("\n");
			printf("\nLIST OF ALL COMMANDS:\n");
			printf("\nHELP - DISPLAYS HELP SCREEN\nCMD - ENTERS CMD MODE\nCLEAR - CLEARS USER INPUT\n");
		}

		else
		{
			printf("\nERROR CODE 1 --- WRONG COMMAND / COMMAND NOT FOUND\n");
		}

		printf("\n");        
	}
}