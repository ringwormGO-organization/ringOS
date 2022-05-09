#pragma once

#include "GUIInclude.hpp"

#define TASKBAR_COLOR 0xff00ffff
#define STARTMENU_COLOR 0xff00ffff
#define SUBMENU_COLOR 0x00008B

#define EDGE_COLOR 0x580002
#define EDGE_HEIGHT 30
#define BUTTONS 2

#define CALCULATOR_COLOR 0xffcc0000

namespace GUI
{
    class Basic
    {
        public:
            void Rectangle(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
            void Square(size_t x, size_t y, size_t width, size_t height, uint32_t colour);
    };

    struct Canvas
    {
        uint64_t width;
        uint64_t height;
    };
    
    struct TaskBar
    {
        size_t taskbar_x;
        size_t taskbar_y;
        size_t taskbar_width;
        size_t taskbar_height;
        uint32_t taskbar_colour = 0xff00ffff;
    };

    struct Windows_close
    {
        long xbuttonclose;
        long ybuttonclose;
        long xbuttonminus;
        long ybuttonminus;
    };

    struct SubMenu
    {
        int type;

        long x;
        long y;
        long width;
        long height;
    };

    struct Application
    {
        bool status;
        int type;
        const char* name;

        long x;
        long y;
        long width;
        long height;
        uint32_t color;
    };

    struct calculator
    {
        bool alReady;

        long int number1;
        long int number2;

        char operation;

        char num1[100];
        char num2[100];

        long int final_number;
    };
    
    Application* Init();
    int UnInit();
    
    class Window : protected Basic
    {
        public:
            bool StartMenuStatus;
            bool SubMenuStatus;
            bool Check();

            int error;

            //resoultion
            uint64_t Width(uint64_t width);
            uint64_t Height(uint64_t height);

            void DrawStartMenu();
            void DrawSubMenu(int type);
            void ClearStartMenu();

            void OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color);
            void CloseApplication();

            void CalculatorLogic(char number);

            void Error(const char* message);

        private:
            int help_i, i_help, help_j, j_help = 0;

            int Edge();
            void AdvancedTaskbar();

            void Calculator();
    };

    extern Basic* BasicStuff;
    extern Window* WindowStuff;

    extern Application* App;

    extern Canvas canvas;
    extern TaskBar taskbar;
    extern SubMenu subMenu;
    extern Windows_close close;

    extern calculator calc;
};