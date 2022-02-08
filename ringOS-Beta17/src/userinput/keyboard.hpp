#pragma once
#include <stdint.h>
#include "../BasicRenderer.hpp"
#include "../library/stdio.hpp"

namespace GUI
{
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

        /* Cursor */
        #define UP 0x48
        #define DOWN 0x50
        #define LEFT 0x4B
        #define RIGHT 0x4D

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

        /* Numbers */
        #define ONE 0x02
        #define TWO 0x03
        #define THREE 0x04
        #define FOUR 0x05
        #define FIVE 0x06
        #define SIX 0x07
        #define SEVEN 0x08
        #define EIGHT 0x09
        #define NINE 0x0A
        #define KEY_ZERO 0x0B

        /* KEYPAD +, -, *, / */
        #define PLUS 0x4E
        #define MINUS 0x4A
        #define MULTIPLY 0x37
        #define DIVIDE 0x35 // also it can be 0xE0

        char Translate(uint8_t scancode, bool uppercase);
    }

    void HandleKeyboard(uint8_t scancode);
}