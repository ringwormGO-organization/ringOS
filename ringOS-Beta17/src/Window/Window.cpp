#include "Window.hpp"

Basic* BasicStuff;
Window* WindowStuff;

BootInfo* bootInfo;

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
    BasicStuff->Rectangle(x, y, width, height, colour);
}




/* ------------------------- WINDOWING SYSTEM ------------------------- */

bool Window::check()
{
    if (winwidth != 0 && winheight != 0 && xbuttonclose != 0 && ybuttonclose != 0 && xbuttonminus != 0 && ybuttonminus != 0)
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

void Window::DrawBMPPicture() //don't call this function, cause Page Fault
{
    //GlobalRenderer->CursorPosition = {-20, -20};

    if (bootInfo->bmpImage->height != bootInfo->framebuffer->Height || bootInfo->bmpImage->width != bootInfo->framebuffer->Width)
    {
        uint32_t previousColour = GlobalRenderer->Colour;
        GlobalRenderer->Colour = 0xffff0000;
        GlobalRenderer->Print("BMP image is not the same resolution as the screen resolution!");
        GlobalRenderer->Next();
        GlobalRenderer->Colour= previousColour;
    }

    // Bottom-up rendering
    for (unsigned int y = 0; y < bootInfo->bmpImage->height; ++y)
    {
        for (unsigned int x = 0; x < bootInfo->bmpImage->width; ++x)
        {
            unsigned int* framebufferPtr = bootInfo->framebuffer->BaseAddress + bootInfo->bmpImage->width * y + x;
            unsigned int* pixPtr = bootInfo->bmpImage->bitmapBuffer + (bootInfo->bmpImage->height - 1 - y) * bootInfo->bmpImage->width + x;
            *framebufferPtr = *pixPtr;
        }
    }
}

void Window::DrawStartMenu()
{
    switch (ResoWidth | ResoHeight)
    {
        case 1920 | 1080:
            BasicStuff->Rectangle(0, 700, 300, 300, STARTMENU_COLOR);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 895};
            GlobalRenderer->Print("CALCULATOR", 2);
            GlobalRenderer->CursorPosition2 = {0, 930};
            GlobalRenderer->Print("SHUTDOWN", 2);
            break;

        case 1366 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, STARTMENU_COLOR);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 588};
            GlobalRenderer->Print("CALCULATOR", 2);
            GlobalRenderer->CursorPosition2 = {0, 620};
            GlobalRenderer->Print("SHUTDOWN", 2);
            break;

        case 1024 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, STARTMENU_COLOR);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 588};
            GlobalRenderer->Print("CALCULATOR", 2);
            GlobalRenderer->CursorPosition2 = {0, 620};
            GlobalRenderer->Print("SHUTDOWN", 2);
            break;
        
        default:
            Error("Resolution unsupported, \nsee kernel.cpp for supported resolution... \nUnable to open Start Menu");
            break;
    }

    GlobalRenderer->Colour = 0xffffffff;
}

void Window::ClearStartMenu()
{
    switch (ResoWidth | ResoHeight)
    {
        case 1920 | 1080:
            BasicStuff->Rectangle(0, 700, 300, 300, 0x00000000);
            break;
        case 1366 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, 0x00000000);
            break;
        case 1024 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, 0x00000000);
            break;
        default:
            Error("Unable to close Start Menu");
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

    Edge(x, y, width, name);
}

void Window::CloseApplication(size_t x, size_t y, size_t width, size_t height)
{
    BasicStuff->Rectangle(x, y, width, height, 0x00000000);
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
void Window::Edge(size_t x, size_t y, size_t width, const char* name)
{
    /* Declare a number of buttons */
    int buttons = BUTTONS;

    /* Check if there is an error */
    if (error == 1)
    {
        goto end;
    }

    /* Deeclare a button positions*/
    xbuttonclose = x + width - 30;
    ybuttonclose = y;

    xbuttonminus = x + width - 60;
    ybuttonminus = y;

    /* Draw a buttons */
    BasicStuff->Rectangle(x, y, width, 30, EDGE_COLOR);

    BasicStuff->Square(x + width - 30, y, 30, 30, 0xffff0000);
    GlobalRenderer->CursorPosition2 = {x + width - 20, y + 5};
    GlobalRenderer->Print("X", 2);

    BasicStuff->Square(x + width - 60, y, 30, 30, 0xffff0000);
    GlobalRenderer->CursorPosition2 = {x + width - 50, y + 5};
    GlobalRenderer->Print("-", 2);

    /* Print a application name */
    GlobalRenderer->CursorPosition2 = {x + 10, y + 5};
    GlobalRenderer->Print(name, 2);

    end:
        int number = 0;
}

void Window::AdvancedTaskbar()
{
    
}

void Window::OpenCalculator(size_t x, size_t y, size_t width, size_t height, uint32_t color)
{
    BasicStuff->Rectangle(x, y, width, height, color);

    Caluclator(x, y, winwidth, winheight);
}

void Window::Caluclator(size_t x, size_t y, size_t width, size_t height)
{
    for (int i = 40; i < 160; i+=40)
    {
        BasicStuff->Square(x + i, y + 80, 30, 30, WHITE);
    }

    for (int i = 40; i < 160; i+=40)
    {
        BasicStuff->Square(x + i, y + 112, 30, 30, WHITE);
    }

    for (int i = 40; i < 160; i+=40)
    {
        BasicStuff->Square(x + i, y + 144, 30, 30, WHITE);
    }
}