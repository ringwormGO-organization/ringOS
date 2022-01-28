#include "keyboard.hpp"

using namespace Renderer;
using namespace GUI;

Application* application;

namespace QWERTYKeyboard 
{

    const char ASCIITable[] = 
    {
         0 ,  0 , '1', '2',
        '3', '4', '5', '6',
        '7', '8', '9', '0',
        '-', '=',  0 ,  0 ,
        'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i',
        'o', 'p', '[', ']',
         0 ,  0 , 'a', 's',
        'd', 'f', 'g', 'h',
        'j', 'k', 'l', ';',
        '\'','`',  0 , '\\',
        'z', 'x', 'c', 'v',
        'b', 'n', 'm', ',',
        '.', '/',  0 , '*',
         0 , ' '
    };

    char Translate(uint8_t scancode, bool uppercase)
    {
        if (scancode > 58) return 0;

        if (uppercase){
            return ASCIITable[scancode] - 32;
        }
        else return ASCIITable[scancode];
    }
}

bool isLeftShiftPressed;
bool isRightShiftPressed;
bool isCapsLockPressed;

char command[20];

void HandleKeyboard(uint8_t scancode)
{
    switch (scancode)
    {
        case LeftShift:
            isLeftShiftPressed = true;
            return;
        case LeftShift + 0x80:
            isLeftShiftPressed = false;
            return;
        case RightShift:
            isRightShiftPressed = true;
            return;
        case RightShift + 0x80:
            isRightShiftPressed = false;
            return;
        case CapsLock:
            if (isCapsLockPressed = true)
                isCapsLockPressed = false;
            else if (isCapsLockPressed == false)
                isCapsLockPressed = true;
            return;
        case Enter:
            GlobalRenderer->Next();
            GlobalRenderer->Print("ringOS> ");
            return;
        case Spacebar:
            GlobalRenderer->PutChar(' ');
            return;
        case BackSpace:
           GlobalRenderer->ClearChar();
           return;
        case ESC:
            if (application->status == true)
                WindowStuff->CloseApplication();
            return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed | isCapsLockPressed);

    if (ascii != 0)
    {
        GlobalRenderer->PutChar(ascii);
    }
}