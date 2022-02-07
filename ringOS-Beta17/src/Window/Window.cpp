#include "Window.hpp"

using namespace GUI::Renderer;

namespace GUI
{
    Basic* BasicStuff;
    Window* WindowStuff;

    Application* App;

    Canvas canvas;
    TaskBar taskbar;
    SubMenu subMenu;
    Windows_close close;

    calculator calc;

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

    Application* Init()
    {
        if (!(App = (Application*)malloc(sizeof(Application))))
        {
            return App;
        }
        else
        {
            
        }
        
        WindowStuff->StartMenuStatus = false;
        WindowStuff->SubMenuStatus = false;

        App->status = false;
        calc.alReady = false;
        calc.operation = '+';

        GlobalRenderer->BMPPicture();
        GlobalRenderer->TaskBar();
        return App;
    }

    int UnInit()
    {
        free(App);
        return 0;
    }

    /* ------------------------- WINDOWING SYSTEM ------------------------- */

    bool Window::Check()
    {
        if (close.xbuttonclose != 0 && close.ybuttonclose 
        != 0 && close.xbuttonminus != 0 && close.ybuttonminus != 0)
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

        StartMenuStatus = true;
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

                if (App->status == true)
                {
                    OpenApplication(App->type, App->x, App->y, App->width, App->height, App->color);
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

        StartMenuStatus = false;
    }

    void Window::OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color)
    {
        const char* name;

        App->x = x;
        App->y = y;
        App->width = width;
        App->height = height;
        App->color = color;
        App->status = true;
        App->type = type;

        switch (type)
        {
            case 1:
                Caluclator();
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
                App->x = 0;
                App->y = 0;
                App->width = 0;
                App->height = 0;
                App->color = 0;
                App->status = false;
                App->type = 0;
                break;
        }

        Edge(x, y, width, name);
    }

    void Window::CloseApplication()
    {
        if (App->type == 1)
        {
            calc.alReady = false;

            calc.number1 = 0;
            calc.operation = '+';
            calc.number2 = 0;

            calc.final_number = 0;
        }

        switch (ResoWidth | ResoHeight)
        {
            case 1920 | 1080:
                GlobalRenderer->BMPPicture();
                GlobalRenderer->TaskBar();

                if (StartMenuStatus == true)
                {
                    DrawStartMenu();

                    if (SubMenuStatus == true)
                    {
                        DrawSubMenu(subMenu.type);
                    }
                }
                App->status = false;
                break;
            
            default:
                Rectangle(App->x, App->y, App->width, App->height, DEF_BLACK);
                App->status = false;
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

        /* Declare a button positions */
        close.xbuttonclose = x + width - 30;
        close.xbuttonminus = y;

        close.ybuttonclose = x + width - 60;
        close.ybuttonminus = y;

        Check();

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

    void Window::Caluclator()
    {
        Rectangle(App->x, App->y, App->width, App->height, App->color);

        long x, y, width, height;

        x = App->x;
        y = App->y;
        width = App->width;
        height = App->height;
        
        //numbers
        for (int i = 40, num = 1; i < 160, num < 4; i+=40, num++)
        {
            Square(x + i, y + 80, 30, 30, WHITE);

            GlobalRenderer->Colour = RED;
            GlobalRenderer->CursorPosition2 = {x + i, y + 80};
            GlobalRenderer->Print(to_string((int64_t)num), 2);
        }

        for (int i = 40, num = 4; i < 160, num < 7; i+=40, num++)
        {
            Square(x + i, y + 112, 30, 30, WHITE);

            GlobalRenderer->Colour = RED;
            GlobalRenderer->CursorPosition2 = {x + i, y + 112};
            GlobalRenderer->Print(to_string((int64_t)num), 2);
        }

        for (int i = 40, num = 7; i < 160, num < 10; i+=40, num++)
        {
            Square(x + i, y + 144, 30, 30, WHITE);

            GlobalRenderer->Colour = RED;
            GlobalRenderer->CursorPosition2 = {x + i, y + 144};
            GlobalRenderer->Print(to_string((int64_t)num), 2);
        }

        // zero
        Square(x + 80, y + 176, 30, 30, WHITE);
        GlobalRenderer->Colour = RED;
        GlobalRenderer->CursorPosition2 = {x + 80, y + 176};
        GlobalRenderer->Print(to_string((int64_t)0), 2);

    	//textbox
        Rectangle(x + 20, y + 40, 260, 25, DEFAULT);

        GlobalRenderer->Colour = DEF_BLACK;
        GlobalRenderer->CursorPosition2 = {x + 25, y + 45};

        if (calc.alReady == false)
            GlobalRenderer->Print(to_string((int64_t)calc.number1), 2);

        if (calc.alReady == true)
            GlobalRenderer->Print(to_string((int64_t)calc.number1), 2);
            GlobalRenderer->PutChar2(calc.operation);
            GlobalRenderer->Print(to_string((int64_t)calc.number2), 2);

            if (calc.final_number != 0)
            {
                GlobalRenderer->PutChar2('=');
                GlobalRenderer->Print(to_string((int64_t)calc.final_number), 2);
            }
            else
            {
                
            }

        GlobalRenderer->Colour = DEFAULT;
    }
}