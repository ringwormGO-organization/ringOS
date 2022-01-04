#include "Window.h"

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


uint64_t Window::Width(uint64_t width)
{
    return ResoWidth = width;
}

uint64_t Window::Height(uint64_t height)
{
    return ResoHeight = height;
}

void Window::DrawBMPPicture()
{

}

void Window::Edge(int buttons, size_t posx, size_t posy, size_t width, uint32_t color)
{
    EdgeStatus = true;

    posxbuttonclose = posx + width - 30;
    posybuttonclose = posy;

    posxbuttonminus = posx + width - 60;
    posybuttonminus = posy;

    GlobalRenderer->Print(to_string((uint64_t)posxbuttonclose));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_string((uint64_t)posybuttonclose));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_string((uint64_t)posxbuttonclose));
    GlobalRenderer->Next();
    GlobalRenderer->Print(to_string((uint64_t)posybuttonminus));
    GlobalRenderer->Next();

    BasicStuff->Rectangle(posx, posy, width, 30, colour);

    BasicStuff->Square(posx + width - 30, posy, 30, 30, 0xffff0000);
    GlobalRenderer->CursorPosition2 = {posx + width - 20, posy + 5};
    GlobalRenderer->Print2("X");

    BasicStuff->Square(posx + width - 60, posy, 30, 30, 0xffff0000);
    GlobalRenderer->CursorPosition2 = {posx + width - 50, posy + 5};
    GlobalRenderer->Print2("-");
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

void Window::OpenCalculator(size_t pos1, size_t pos2, size_t width, size_t height, uint32_t color)
{
    BasicStuff->Rectangle(pos1, pos2, width, height, color);
    Edge(3, pos1, pos2, width, colour);
}

void Window::CloseCalculator()
{
    BasicStuff->Rectangle(300, 300, 300, 300, 0x00000000);
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