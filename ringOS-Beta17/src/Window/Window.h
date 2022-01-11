#pragma once

#include <stdint.h> 

#include "../kernelUtil.h"
#include "../BasicRenderer.h"
#include "../ColorCodes.h"
#include "../Numbers.h"
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
        bool check();

        uint64_t ResoWidth;
        uint64_t ResoHeight;
        uint64_t Width(uint64_t width);
        uint64_t Height(uint64_t height);

        size_t winheight;
        size_t winwidth;
        size_t xbuttonclose;
        size_t ybuttonclose;
        size_t xbuttonminus;
        size_t ybuttonminus;
 
        uint32_t colour = DARK_GREEN2;
        int buttons = 2;
        size_t edgeheight;

        void DrawBMPPicture();

        void DrawStartMenu(uint32_t color);
        void ClearStartMenu();

        void OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color);
        void CloseApplication(size_t x, size_t y, size_t width, size_t height);

        void Error(const char* message);

    private:
        void Edge(int buttons, size_t x, size_t y, size_t width, uint32_t color);

        void OpenCalculator(size_t x, size_t y, size_t width, size_t height, uint32_t color);
        void Caluclator(size_t x, size_t y, size_t width, size_t height);
};

extern Basic* BasicStuff;
extern Window* WindowStuff;