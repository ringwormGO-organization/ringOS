#pragma once
#include <stdint.h>
#include "../BasicRenderer.hpp"
#include "../library/string.hpp"

namespace QWERTYKeyboard
{
    /* Capital letters */
    #define LeftShift 0x2A
    #define RightShift 0x36
    #define CapsLock 0x3A

    /* Alt keys */
    #define LALT 0x38
    #define RALT 0xE0
    #define ALTGR 0x38

    /* Enter, BackSpace, Spacebar */
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39

    /* ESC key */
    #define ESC 0x01

    /* F keys */
    #define F1 0x3B
    #define F2 0x3C
    #define F3 0x3D
    #define F4 0x3E
    #define F5 0x3F
    #define F6 0x40
    #define F7 0x41
    #define F8 0x42
    #define F9 0x43
    #define F10 0x44
    #define F11 0x57
    #define F12 0x58

    char Translate(uint8_t scancode, bool uppercase);
}

void HandleKeyboard(uint8_t scancode);