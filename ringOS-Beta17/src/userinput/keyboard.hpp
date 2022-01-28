#pragma once
#include <stdint.h>
#include "../BasicRenderer.hpp"
#include "../library/string.hpp"

namespace QWERTYKeyboard
{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define CapsLock 0x3A
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39
    #define ESC 0x01


    char Translate(uint8_t scancode, bool uppercase);
}

void HandleKeyboard(uint8_t scancode);