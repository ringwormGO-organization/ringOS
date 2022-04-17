#include "Window.hpp"

using namespace GUI::Text;

namespace GUI
{
    /* Getting required structs */
    Basic* BasicStuff;
    Window* WindowStuff;

    Application* App;

    Canvas canvas;
    TaskBar taskbar;
    SubMenu subMenu;
    Windows_close close;

    calculator calc;

    /* Function which draw rectangle */
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

    /* Function which draw square */
    void Basic::Square(size_t x, size_t y, size_t width, size_t height, uint32_t colour)
    {
        Rectangle(x, y, width, height, colour);
    }

    /* malloc a Application struct and load taskbar and background picture */
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

    /* free an application */
    int UnInit()
    {
        free(App);
        return 0;
    }

    /* ------------------------- WINDOWING SYSTEM ------------------------- */

    /* Checking if something is zero */
    bool Window::Check()
    {
        if (close.xbuttonclose != 0 || close.ybuttonclose 
        != 0 || close.xbuttonminus != 0 || close.ybuttonminus != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /* Returning width to canvas.width */
    uint64_t Window::Width(uint64_t width)
    {
        return canvas.width = width;
    }

    /* Returning height to canvas.height */
    uint64_t Window::Height(uint64_t height)
    {
        return canvas.height = height;
    }

    /* Drawing Start Menu */
    void Window::DrawStartMenu()
    {
        Rectangle(0, canvas.height - 380, 300, 300, STARTMENU_COLOR);
        taskbar.taskbar_x = 0;
        taskbar.taskbar_y = canvas.height - 380;
        taskbar.taskbar_width = 300;
        taskbar.taskbar_height = 300;

        GlobalRenderer->Colour = 0xffff0000;
        GlobalRenderer->CursorPosition2 = {0, (long)canvas.height - 185};
        GlobalRenderer->Print("CALCULATOR", 2);
        GlobalRenderer->CursorPosition2 = {0, (long)canvas.height - 150};
        GlobalRenderer->Print("POWER", 2);
        
        GlobalRenderer->Colour = 0xffffffff;

        StartMenuStatus = true;
    }

    /* Drawing Sub Menu */
    void Window::DrawSubMenu(int type)
    {
        subMenu.x = taskbar.taskbar_x + 80;
        subMenu.y = canvas.height - 150;

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

    /* Closing Start Menu */
    void Window::ClearStartMenu()
    {
        switch (canvas.width | canvas.height)
        {
            case 1920 | 1080:
                GlobalRenderer->BMPPicture();
                GlobalRenderer->TaskBar();

                if (App->status == true)
                {
                    OpenApplication(App->type, App->x, App->y, App->width, App->height, App->color);
                }

                GlobalRenderer->Colour = RED;
                GlobalRenderer->CursorPosition = {0, (long)canvas.height - 80};
                GlobalRenderer->Print("START");
                GlobalRenderer->Colour = DEFAULT;
                break;
            default:
                Rectangle(0, canvas.height - 380, 300, 300, 0x00000000);
                break;
        }

        GlobalRenderer->Colour = 0xffffffff;

        StartMenuStatus = false;
    }

    /* 
     * Opening application, parameters are going to application struct
     *
     * 1 == calculator 
     * other == error
     * 
    */
    void Window::OpenApplication(int type, size_t x, size_t y, size_t width, size_t height, uint32_t color)
    {
        const char* name;

        App->x = x;
        App->y = y;
        App->width = width;
        App->height = height;
        App->color = color;

        /* Checking type of application */
        switch (type)
        {
            case 1:
                Caluclator();
                name = "Calculator";
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
                return;
                break;
        }

        App->status = true;
        App->type = type;
        App->name = name;

        Edge();
    }

    /* Closing application and drawing background again and Start Menu if it is open before */
    void Window::CloseApplication()
    {
        /* Deafulting changes in calculator */
        if (App->type == 1)
        {
            calc.alReady = false;

            calc.number1 = 0;
            calc.operation = '+';
            calc.number2 = 0;

            calc.final_number = 0;
        }

        /* Checking resolution */
        switch (canvas.width | canvas.height)
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

    /* Some calculator stuff */
    void Window::CaclualtorLogic(char number)
    {
        /* Checking if we try to change first or second number */
        switch (calc.alReady)
        {
            case false:
                calc.number1 = tonum(number); /* First number is equal to our parameter which is equal to keyboard input */
                Caluclator();
                break;

            case true:
                calc.number2 = tonum(number); /* Second number is equal to our parameter which is equal to keyboard input */
                Caluclator();
                break;
            
            default:
                break;
        }

        switch (calc.alReady)
        {
            case false:
                calc.num1[help_i] = number;
                help_i++;
                break;

            case true:
                calc.num2[help_j] = number;
                help_j++;
                break;

            default:
                break;
        }

        /* Calling Calculator function to draw it again which this change */
        Caluclator();
    }

    /* Printing an error which second cursor position */
    void Window::Error(const char* message)
    {
        GlobalRenderer->Colour = RED;
        GlobalRenderer->Next();
        GlobalRenderer->Print(message);
        GlobalRenderer->Next();
        GlobalRenderer->Colour = DEFAULT;
    }


    /*             
     * Draw Edge at top of window               
    */
    int Window::Edge()
    {
        /* Declare a number of buttons */
        int buttons = BUTTONS;

        /* Check if there is an error */
        if (error == 1)
        {
            return 1;
        }

        /* Check if app parameters are not equal to zero */
        if (App->x == 0 || App->y == 0 || App->width == 0 || App->height == 0
        || App->color == 0 || App->status != true || App->type == 0 || App->name == "0")
        {
            return 1;
        }

        /* Set up window parameters */
        bool status = App->status;
        int type = App->type;
        const char* name = App->name;

        long x, y, width, height;
        x = App->x;
        y = App->y;
        width = App->width;
        height = App->height;

        uint32_t color = App->color;

        /* Declare a button positions */
        close.xbuttonclose = x + width - 30;
        close.xbuttonminus = y;

        close.ybuttonclose = x + width - 60;
        close.ybuttonminus = y;

        /* Set a color for text */
        GlobalRenderer->Colour = DEFAULT;

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

    /* Something for drawing active application on taskbar */
    void Window::AdvancedTaskbar()
    {
        
    }

    /* Calculator */
    void Window::Caluclator()
    {
        /* Drawing window */
        Rectangle(App->x, App->y, App->width, App->height, App->color);

        /* Declare window parameters */
        long x, y, width, height;
        x = App->x;
        y = App->y;
        width = App->width;
        height = App->height;
        
        /* Printing numbers 1 - 9 */ 
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

        /* number zero */
        Square(x + 80, y + 176, 30, 30, WHITE);
        GlobalRenderer->Colour = RED;
        GlobalRenderer->CursorPosition2 = {x + 80, y + 176};
        GlobalRenderer->Print(to_string((int64_t)0), 2);

    	/* textbox */
        Rectangle(x + 20, y + 40, 260, 25, DEFAULT);

        /* Calling Edge() function */
        Edge();

        /* Printing to textbox */
        GlobalRenderer->Colour = DEF_BLACK;
        GlobalRenderer->CursorPosition2 = {x + 25, y + 45};

        if (calc.alReady == false)
            GlobalRenderer->Print(to_string((int64_t)calc.number1), 2);

        if (calc.alReady == true)
            GlobalRenderer->Print(to_string((int64_t)calc.number1), 2);
            GlobalRenderer->Print(char2str(calc.operation), 2);
            GlobalRenderer->Print(to_string((int64_t)calc.number2), 2);

            if (calc.final_number != 0)
            {
                GlobalRenderer->Print(char2str('='), 2);
                GlobalRenderer->Print(to_string((int64_t)calc.final_number), 2);
            }
            else
            {
                
            }

        /* Setting color to default */
        GlobalRenderer->Colour = DEFAULT;
    }
}