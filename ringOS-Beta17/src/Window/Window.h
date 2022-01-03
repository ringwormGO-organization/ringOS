#pragma once

#include <stdint.h> 

#include "../kernelUtil.h"
#include "../BasicRenderer.h"
#include "../scheduling/pit/pit.h"
#include "../userinput/keyboard.h"
#include "../shutdown.h"
#include "../Reboot.h"

class Basic
{
    public:
        void Rectangle(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
        void Square(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
};

class Window
{
    public:
        bool StartMenuStatus;

        uint64_t ResoWidth;
        uint64_t ResoHeight;
        uint64_t Width(uint64_t width);
        uint64_t Height(uint64_t height);

        uint32_t colour = 0x580002;

        void Edge(int buttons, size_t pos1, size_t pos2, size_t width, uint32_t color);

        void DrawStartMenu(uint32_t color);
        void ClearStartMenu();

        void OpenCalculator(size_t pos1, size_t pos2, size_t width, size_t height, uint32_t color);
        void CloseCalculator();

        void Error(const char* message);
};

extern Basic* BasicStuff;
extern Window* WindowStuff;