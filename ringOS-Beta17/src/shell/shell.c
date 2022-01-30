
#include "screen.h"
#include "kb.h"
#include "string.h"

int shell()
{
       clearScreen();
       print("\n");

       while (1)
       {
                print("\nUser> ");
                
                string ch = readStr();

                if(strEql(ch,"cmd"))
                {
                        print("\nYou are already in CMD mode\n");
                }
                else if(strEql(ch, "help"))
                {
                        print("\n");
                        print("\nLIST OF ALL COMMANDS:\n");
                        print("\nHELP - DISPLAYS HELP SCREEN\nCMD - ENTERS CMD MODE\nCLEAR - CLEARS USER INPUT\n");
                }
                
                else
                {
                        print("\nERROR CODE 1 --- WRONG COMMAND / COMMAND NOT FOUND\n");
                }
                
                print("\n");        
       }

}
