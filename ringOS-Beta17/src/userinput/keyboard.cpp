#include "keyboard.hpp"

using namespace GUI::Renderer;

namespace GUI
{
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
                isCapsLockPressed = true;
                return;

            case CapsLock + 0x80:
                isCapsLockPressed = false;
                return;

    /* --------------------------------------------------------------- */  
            case Enter:
                if (App->status == true && App->type == 1)
                {
                    switch (calc.operation)
                    {
                        case '+':
                            calc.final_number = calc.number1 + calc.number2;
                            WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                            break;

                        case '-':
                            calc.final_number = calc.number1 - calc.number2;
                            WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                            break;

                        case '*':
                            calc.final_number = calc.number1 * calc.number2;
                            WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                            break;

                        case '/':
                            calc.final_number = calc.number1 / calc.number2;
                            WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                            break;
                        
                        default:
                            break;
                    }
                }
                else
                {
                    printf("\nringOS> ");
                }
                return;

            case Spacebar:
                GlobalRenderer->PutChar(' ');
                return;

            case BackSpace:
            GlobalRenderer->ClearChar();
            return;

    /* --------------------------------------------------------------- */
            case ESC:
                if (App->status == true)
                    WindowStuff->CloseApplication();
                return;

    /* --------------------------------------------------------------- */
            case LEFT:
                if (App->status == true && App->type == 1)
                    calc.alReady = false;
                return;

            case RIGHT:
                if (App->status == true && App->type == 1)
                    calc.alReady = true;
                return;

    /* --------------------------------------------------------------- */    
            case F1:
                GlobalRenderer->CursorPosition2 = {0, 0};
                if (WindowStuff->StartMenuStatus == true)
                {
                    WindowStuff->ClearStartMenu();
                }
                else if (WindowStuff->StartMenuStatus == false)
                {
                    WindowStuff->DrawStartMenu();
                }
                return;

            case F2:
                GlobalRenderer->CursorPosition2 = {0, 0};
                if (WindowStuff->StartMenuStatus == true) 
                { 
                    if (WindowStuff->SubMenuStatus == true)
                    {
                        WindowStuff->DrawSubMenu(1);
                    }
                
                    else if (WindowStuff->SubMenuStatus == false)
                    {
                        WindowStuff->DrawSubMenu(2);
                    }
                }
                return;

            case F3:
                GlobalRenderer->CursorPosition2 = {0, 0};
                WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                return;

            case F4:
                if (App->status == true)
                {
                    WindowStuff->CloseApplication();
                }
                else if (App->status == false)
                {
                    Shutdown();
                }
                return;

    /* --------------------------------------------------------------- */
            case ONE:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 1;
                    if (calc.alReady == true)
                        calc.number2 = 1;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('1');
                }
                return;

            case TWO:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 2;
                    if (calc.alReady == true)
                        calc.number2 = 2;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('2');
                }
                return;

            case THREE:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 3;
                    if (calc.alReady == true)
                        calc.number2 = 3;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('3');
                }
                return;

            case FOUR:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 4;
                    if (calc.alReady == true)
                        calc.number2 = 4;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('4');
                }
                return;

            case FIVE:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 5;
                    if (calc.alReady == true)
                        calc.number2 = 5;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('5');
                }
                return;

            case SIX:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 6;
                    if (calc.alReady == true)
                        calc.number2 = 6;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('6');
                }
                return;

            case SEVEN:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 7;
                    if (calc.alReady == true)
                        calc.number2 = 7;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('7');
                }
                return;

            case EIGHT:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 8;
                    if (calc.alReady == true)
                        calc.number2 = 8;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('8');
                }
                return;

            case NINE:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 9;
                    if (calc.alReady == true)
                        calc.number2 = 9;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('9');
                }
                return;

            case KEY_ZERO:
                if (App->status == true && App->type == 1)
                {
                    if (calc.alReady == false)
                        calc.number1 = 0;
                    if (calc.alReady == true)
                        calc.number2 = 0;

                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                }
                else
                {
                    GlobalRenderer->PutChar('0');
                }
                return;

    /* --------------------------------------------------------------- */
            case PLUS:
                if (App->status == true && App->type == 1)
                    calc.operation = '+';
                if (App->status == true && App->type == 1)
                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                return;

            case MINUS:
                if (App->status == true && App->type == 1)
                    calc.operation = '-';

                if (App->status == true && App->type == 1)
                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                return;

            case MULTIPLY:
                if (App->status == true && App->type == 1)
                    calc.operation = '*';

                if (App->status == true && App->type == 1)
                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                return;

            case DIVIDE:
                if (App->status == true && App->type == 1)
                    calc.operation = '/';

                if (App->status == true && App->type == 1)
                    WindowStuff->OpenApplication(1, 300, 300, 300, 300, CALCULATOR_COLOR);
                return;
        }

        char ascii = QWERTYKeyboard::Translate(scancode, isLeftShiftPressed | isRightShiftPressed | isCapsLockPressed);

        if (ascii != 0)
        {
            GlobalRenderer->PutChar(ascii);          
        }
    }
}