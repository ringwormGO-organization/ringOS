#pragma once

#include <stdint.h> 

#include "shell.hpp"
#include "../kernelUtil.h"
#include "../BasicRenderer.hpp"
#include "../ColorCodes.h"
#include "../scheduling/pit/pit.hpp"
#include "../memory/heap.hpp"
#include "../shutdown.hpp"
#include "../Reboot.hpp"

#define TASKBAR_COLOR 0xff00ffff
#define STARTMENU_COLOR 0xff00ffff
#define EDGE_COLOR 0x580002
#define EDGE_HEIGHT 30
#define BUTTONS 2

class Basic
{
    public:
        void Rectangle(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
        void Square(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
};

class Window : Basic
{
    public:
        bool StartMenuStatus;
        bool check();

        int error;

        //resoultion
        uint64_t ResoWidth;
        uint64_t ResoHeight;
        uint64_t Width(uint64_t width);
        uint64_t Height(uint64_t height);

        //taskbar
        size_t taskbar_x;
        size_t taskbar_y;
        size_t taskbar_width;
        size_t taskbar_height;
        uint32_t taskbar_colour = 0xff00ffff;

        //window
        size_t winheight;
        size_t winwidth;
        size_t xbuttonclose;
        size_t ybuttonclose;
        size_t xbuttonminus;
        size_t ybuttonminus;

        void DrawBMPPicture();

        void DrawStartMenu();
        void ClearStartMenu();

        void OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color);
        void CloseApplication(size_t x, size_t y, size_t width, size_t height);

        void Error(const char* message);

    private:
        void Edge(size_t x, size_t y, size_t width, const char* name);
        void AdvancedTaskbar();

        void OpenCalculator(size_t x, size_t y, size_t width, size_t height, uint32_t color);
        void Caluclator(size_t x, size_t y, size_t width, size_t height);
};

extern Basic* BasicStuff;
extern Window* WindowStuff;