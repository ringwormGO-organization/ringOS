#include "Window.h"

Basic* BasicStuff;
Window* WindowStuff;

//BootInfo* bootInfo;

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


uint64_t Window::Width(uint64_t width)
{
    return ResoWidth = width;
}

uint64_t Window::Height(uint64_t height)
{
    return ResoHeight = height;
}


void Window::Edge(int buttons, size_t pos1, size_t pos2, size_t width, uint32_t color)
{
    BasicStuff->Rectangle(pos1, pos2, width, 30, colour);
}

void Window::DrawStartMenu(uint32_t color)
{
    switch (ResoWidth | ResoHeight)
    {
        case 1920 | 1080:
            BasicStuff->Rectangle(0, 700, 300, 300, color);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 895};
            GlobalRenderer->Print2("CALCULATOR");
            GlobalRenderer->CursorPosition2 = {0, 930};
            GlobalRenderer->Print2("SHUTDOWN");
            break;

        case 1366 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, color);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 588};
            GlobalRenderer->Print2("CALCULATOR");
            GlobalRenderer->CursorPosition2 = {0, 620};
            GlobalRenderer->Print2("SHUTDOWN");
            break;

        case 1024 | 768:
            BasicStuff->Rectangle(0, 388, 300, 300, color);
            GlobalRenderer->Colour = 0xffff0000;
            GlobalRenderer->CursorPosition2 = {0, 588};
            GlobalRenderer->Print2("CALCULATOR");
            GlobalRenderer->CursorPosition2 = {0, 620};
            GlobalRenderer->Print2("SHUTDOWN");
            break;
        
        default:
            Error("Resolution unsupported, see kernel.cpp for supported resolution... Unable to open Start Menu");
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
            BasicStuff->Rectangle(0, 488, 200, 200, 0x00000000);
            break;
        case 1024 | 768:
            BasicStuff->Rectangle(0, 488, 200, 200, 0x00000000);
            break;
        default:
            Error("Unable to close Start Menu");
            break;
    }

    GlobalRenderer->Colour = 0xffffffff;
}

void Window::OpenCalculator(size_t pos1, size_t pos2, size_t width, size_t height, uint32_t color)
{
    BasicStuff->Rectangle(pos1, pos2, width, height, color);
    Edge(3, pos1, pos2, width, colour);
}

void Window::CloseCalculator()
{

}

void Window::Error(const char* message)
{
    BasicStuff->Rectangle(200, 200, 300, 300, 0xffff0000);
    GlobalRenderer->CursorPosition2 = {240, 240};
    GlobalRenderer->Print2(message);

    PIT::Sleep(20000);

    BasicStuff->Rectangle(200, 200, 300, 300, 0x00000000);
    GlobalRenderer->Next();

    GlobalRenderer->Colour = 0xffffffff;
}