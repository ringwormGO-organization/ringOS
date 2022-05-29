#include "keyboard.hpp"

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

        if (uppercase)
            return ASCIITable[scancode] - 32;
        else return ASCIITable[scancode];
    }
}

bool isLeftShiftPressed;
bool isRightShiftPressed;

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
        case Enter:
            e9_putc('\n');
            return;
        case Spacebar:
            e9_putc(' ');
            return;
        case BackSpace:
            /* todo */
            return;
    }

    char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed);

    if (ascii != 0)
    {
        e9_putc(ascii);
    }
}