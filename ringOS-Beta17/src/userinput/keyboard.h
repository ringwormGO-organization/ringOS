#pragma once
#include <stdint.h>
#include "../BasicRenderer.h"
#include "../Window/Window.h"

namespace QWERTYKeyboard
{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define CapsLock 0x3A
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39


    char Translate(uint8_t scancode, bool uppercase);
}

void HandleKeyboard(uint8_t scancode);