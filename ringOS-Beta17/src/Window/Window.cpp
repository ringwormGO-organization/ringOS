#include "Window.hpp"

using namespace Renderer;

namespace GUI
{
    Basic* BasicStuff;
    Window* WindowStuff;

    void Basic::Rectangle(size_t x, size_t y, size_t width, size_t height, uint32_t colour)
    {
        for (size_t y1 = y; y1 < y + height; y1++)
        {
            for (size_t x1 = x; x1 < x + width; x1++)
            {
                GlobalRenderer->PutPix(x1, y1, colour);
            }
        }
    }

    void Basic::Square(size_t x, size_t y, size_t width, size_t height, uint32_t colour)
    {
        Rectangle(x, y, width, height, colour);
    }

    Canvas canvas;
    TaskBar taskbar;
    SubMenu subMenu;
    window win;
    windowStatus winStatus;

    App* app;

    void NewApp(int type)
    {
        switch (type)
        {
            case 1:
                App* calculator;
                break;
            
            default:
                break;
        }
    }

    int Init()
    {
        if (!(app = (App*)malloc(sizeof(App))))
        {
            return 1;
        }
        else
        {
            
        }
        
        GlobalRenderer->BMPPicture();
        GlobalRenderer->TaskBar();
        return 0; 
    }

    int UnInit()
    {
        free(app);
        return 0;
    }

    /* ------------------------- WINDOWING SYSTEM ------------------------- */

    bool Window::check()
    {
        if (win.winwidth != 0 && win.winheight != 0 && win.xbuttonclose != 0 && win.ybuttonclose 
        != 0 && win.xbuttonminus != 0 && win.ybuttonminus != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    uint64_t Window::Width(uint64_t width)
    {
        return ResoWidth = width;
    }

    uint64_t Window::Height(uint64_t height)
    {
        return ResoHeight = height;
    }

    void Window::DrawStartMenu()
    {
        Rectangle(0, ResoHeight - 380, 300, 300, STARTMENU_COLOR);
        taskbar.taskbar_x = 0;
        taskbar.taskbar_y = ResoHeight - 380;
        taskbar.taskbar_width = 300;
        taskbar.taskbar_height = 300;

        GlobalRenderer->Colour = 0xffff0000;
        GlobalRenderer->CursorPosition2 = {0, ResoHeight - 185};
        GlobalRenderer->Print("CALCULATOR", 2);
        GlobalRenderer->CursorPosition2 = {0, ResoHeight - 150};
        GlobalRenderer->Print("POWER", 2);
        
        GlobalRenderer->Colour = 0xffffffff;
    }

    void Window::DrawSubMenu(int type)
    {
        subMenu.x = taskbar.taskbar_x + 80;
        subMenu.y = ResoHeight - 150;

        subMenu.width = 100;
        subMenu.height = 100;

        switch (type)
        {
            case 1: //close
                subMenu.type = 1;

                if (StartMenuStatus == false)
                {
                    Square(subMenu.x, subMenu.y, subMenu.width, subMenu.height, DEF_BLACK);
                }
                else if (StartMenuStatus == true)
                {
                    Square(subMenu.x, subMenu.y, subMenu.width, subMenu.height, STARTMENU_COLOR);
                }
                else
                {

                }

                SubMenuStatus = false;
                break;

            case 2: //power
                subMenu.type = 2;

                Square(subMenu.x, subMenu.y, subMenu.width, subMenu.height, SUBMENU_COLOR);

                GlobalRenderer->CursorPosition2 = {subMenu.x, subMenu.y};
                GlobalRenderer->Print("SHUTDOWN", 2);

                GlobalRenderer->CursorPosition2 = {subMenu.x, subMenu.y + 32};
                GlobalRenderer->Print("REBOOT", 2);

                GlobalRenderer->CursorPosition2 = {subMenu.x, subMenu.y + 64};
                GlobalRenderer->Print("CLOSE", 2);
                
                SubMenuStatus = true;

                break;
            
            default:
                break;
        }
    }

    void Window::ClearStartMenu()
    {
        switch (ResoWidth | ResoHeight)
        {
            case 1920 | 1080:
                GlobalRenderer->BMPPicture();
                GlobalRenderer->TaskBar();

                if (winStatus.status == true)
                {
                    OpenApplication(app->sType, app->x, app->y, app->width, app->height, app->color);
                }

                GlobalRenderer->Colour = RED;
                GlobalRenderer->CursorPosition = {0, (long) ResoHeight - 80};
                GlobalRenderer->Print("START");
                GlobalRenderer->Colour = DEFAULT;
                break;
            default:
                Rectangle(0, ResoHeight - 380, 300, 300, 0x00000000);
                break;
        }

        GlobalRenderer->Colour = 0xffffffff;
    }

    void Window::OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color)
    {
        const char* name;

        switch (type)
        {
            case 1:
                OpenCalculator(x, y, width, height, 0xffcc0000);
                name = "Calculator";
                break;

            case 2:
                ShellStuff->shellx = x;
                ShellStuff->shelly = y;
                ShellStuff->ShellInit();    
                name = "Shell";
                break;
            
            default:
                Error("Application unsupproted... Unable to open it");
                error = 1;
                break;
        }

        

        app->x = x;
        app->y = y;
        app->width = width;
        app->height = height;
        app->color = color;

        winStatus.status = true;
        winStatus.sType = type;
        Edge(x, y, width, name);
    }

    void Window::CloseApplication()
    {
        switch (ResoWidth | ResoHeight)
        {
            case 1920 | 1080:
                GlobalRenderer->BMPPicture();

                if (StartMenuStatus == true)
                {
                    DrawStartMenu();

                    if (SubMenuStatus == true)
                    {
                        DrawSubMenu(subMenu.type);
                    }
                }
                break;
            
            default:
                Rectangle(app->x, app->y, app->width, app->height, DEF_BLACK);
                break;
        }
    }

    void Window::Error(const char* message)
    {
        GlobalRenderer->Colour = RED;
        GlobalRenderer->Next();
        GlobalRenderer->Print(message);
        GlobalRenderer->Next();
        GlobalRenderer->Colour = DEFAULT;
    }


    /*                              PRIVATE                             */
    int Window::Edge(long x, long y, long width, const char* name)
    {
        /* Declare a number of buttons */
        int buttons = BUTTONS;

        /* Check if there is an error */
        if (error == 1)
        {
            return 1;
        }

        /* Deeclare a button positions*/
        win.xbuttonclose = x + width - 30;
        win.ybuttonclose = y;

        win.xbuttonminus = x + width - 60;
        win.ybuttonminus = y;

        /* Draw a buttons */
        Rectangle(x, y, width, 30, EDGE_COLOR);

        Square(x + width - 30, y, 30, 30, 0xffff0000);
        GlobalRenderer->CursorPosition2 = {x + width - 20, y + 5};
        GlobalRenderer->Print("X", 2);

        Square(x + width - 60, y, 30, 30, 0xffff0000);
        GlobalRenderer->CursorPosition2 = {x + width - 50, y + 5};
        GlobalRenderer->Print("-", 2);

        /* Print a application name */
        GlobalRenderer->CursorPosition2 = {x + 10, y + 5};
        GlobalRenderer->Print(name, 2);

        return 0;
    }

    void Window::AdvancedTaskbar()
    {
        
    }

    void Window::OpenCalculator(size_t x, size_t y, size_t width, size_t height, uint32_t color)
    {
        Rectangle(x, y, width, height, color);

        Caluclator(x, y, win.winwidth, win.winheight);
    }

    void Window::Caluclator(size_t x, size_t y, size_t width, size_t height)
    {
        for (int i = 40; i < 160; i+=40)
        {
            Square(x + i, y + 80, 30, 30, WHITE);
        }

        for (int i = 40; i < 160; i+=40)
        {
            Square(x + i, y + 112, 30, 30, WHITE);
        }

        for (int i = 40; i < 160; i+=40)
        {
            Square(x + i, y + 144, 30, 30, WHITE);
        }
    }
}