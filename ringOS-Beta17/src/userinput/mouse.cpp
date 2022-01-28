#include "mouse.hpp"

using namespace Renderer;
using namespace GUI;

uint8_t cursor[]
{
    0b10000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11100000, 0b00000000,
    0b11110000, 0b00000000,
    0b11111000, 0b00000000,
    0b11111100, 0b00000000,
    0b11111110, 0b00000000,
    0b11111111, 0b00000000,
    0b11111111, 0b10000000,
    0b11111111, 0b11000000,
    0b11111111, 0b11100000,
    0b11111111, 0b11110000,
    0b11111111, 0b11110000,
    0b11111111, 0b00000000,
    0b11110111, 0b10000000,
    0b11100111, 0b10000000,
    0b11000011, 0b11100000,
    0b00000011, 0b11100000,
    0b00000001, 0b10011000,
};

uint8_t cursor2[]
{
    0b10000000, 0b00000000,
    0b11000000, 0b00000000,
    0b11100000, 0b00000000,
    0b11110000, 0b00000000,
    0b11111000, 0b00000000,
    0b11111100, 0b00000000,
    0b11111110, 0b00000000,
    0b11111111, 0b00000000,
    0b11111111, 0b10000000,
    0b11111111, 0b11000000,
    0b11111111, 0b11100000,
    0b11111111, 0b11110000,
    0b11111111, 0b11110000,
    0b11111111, 0b00000000,
    0b11110111, 0b10000000,
    0b11100111, 0b10000000,
    0b11000011, 0b11100000,
    0b00000011, 0b11100000,
    0b00000001, 0b10011000,
};

void MouseWait()
{
    uint64_t timeout = 100000;
    while (timeout--){
        if ((inb(0x64) & 0b10) == 0){
            return;
        }
    }
}

void MouseWaitInput()
{
    uint64_t timeout = 100000;
    while (timeout--){
        if (inb(0x64) & 0b1){
            return;
        }
    }
}

void MouseWrite(uint8_t value)
{
    MouseWait();
    outb(0x64, 0xD4);
    MouseWait();
    outb(0x60, value);
}

uint8_t MouseRead()
{
    MouseWaitInput();
    return inb(0x60);
}

uint8_t MouseCycle = 0;
uint8_t MousePacket[4];
bool MousePacketReady = false;
Point MousePosition;
Point MousePositionOld;

void HandlePS2Mouse(uint8_t data)
{

    ProcessMousePacket();
    static bool skip = true;
    if (skip) { skip = false; return; }

    switch(MouseCycle)
    {
        case 0:
           
            if ((data & 0b00001000) == 0) break;
            MousePacket[0] = data;
            MouseCycle++;
            break;
        case 1:
           
            MousePacket[1] = data;
            MouseCycle++;
            break;
        case 2:
            
            MousePacket[2] = data;
            MousePacketReady = true;
            MouseCycle = 0;
            break;
    }
}

void ProcessMousePacket()
{
    if (!MousePacketReady) return;

        bool xNegative, yNegative, xOverflow, yOverflow;

        if (MousePacket[0] & PS2XSign)
        {
            xNegative = true;
        }
        else xNegative = false;

        if (MousePacket[0] & PS2YSign)
        {
            yNegative = true;
        }
        else yNegative = false;

        if (MousePacket[0] & PS2XOverflow)
        {
            xOverflow = true;
        }
        else xOverflow = false;

        if (MousePacket[0] & PS2YOverflow)
        {
            yOverflow = true;
        }
        else yOverflow = false;

        if (!xNegative)
        {
            MousePosition.X += MousePacket[1];
            if (xOverflow){
                MousePosition.X += 255;
            }
        } 
        else
        {
            MousePacket[1] = 256 - MousePacket[1];
            MousePosition.X -= MousePacket[1];
            if (xOverflow)
            {
                MousePosition.X -= 255;
            }
        }

        if (!yNegative)
        {
            MousePosition.Y -= MousePacket[2];
            if (yOverflow){
                MousePosition.Y -= 255;
            }
        } 
        else
        {
            MousePacket[2] = 256 - MousePacket[2];
            MousePosition.Y += MousePacket[2];
            if (yOverflow){
                MousePosition.Y += 255;
            }
        }


        Clear();
        Draw();


        MousePacketReady = false;
        MousePositionOld = MousePosition;
}

namespace GUI
{
    Windows_close cls;
    SubMenu sub;

    void Draw()
    {
        if (MousePosition.X < 0) MousePosition.X = 0;
        if (MousePosition.X > GlobalRenderer->TargetFramebuffer->Width-1) MousePosition.X = GlobalRenderer->TargetFramebuffer->Width-1;

        if (MousePosition.Y < 0) MousePosition.Y = 0;
        if (MousePosition.Y > GlobalRenderer->TargetFramebuffer->Height-1) MousePosition.Y = GlobalRenderer->TargetFramebuffer->Height-1;

        
        GlobalRenderer->DrawOverlayMouseCursor(cursor, MousePosition, 0xffffffff);

        if (MousePacket[0] & PS2Leftbutton)
        {
            if (MousePosition.Y >= WindowStuff->ResoHeight - 80 && MousePosition.X <= 100)
            {
                if (WindowStuff->StartMenuStatus == true)
                {
                    WindowStuff->ClearStartMenu();
                }
                else
                {
                    WindowStuff->DrawStartMenu();
                }
            }
            else if (MousePosition.Y >= cls.ybuttonclose 
            && MousePosition.Y <= cls.ybuttonclose + 20 && MousePosition.X >= cls.xbuttonclose 
            && MousePosition.X <= cls.xbuttonclose + 20)
            {
                WindowStuff->CloseApplication();
            }
            
            switch (WindowStuff->ResoWidth | WindowStuff->ResoHeight)
            {
                case 1920 | 1080:
                    if (WindowStuff->SubMenuStatus == true)
                    {
                        if (MousePosition.Y > 930 && MousePosition.Y < 950
                        && MousePosition.X > 75 && MousePosition.X < 200)
                        {
                            UnInit();
                            Shutdown();
                        }
                        else if (MousePosition.Y > 951 && MousePosition.Y < 980
                        && MousePosition.X < 200)
                        {
                            UnInit();
                            Reboot();
                        }
                        else if (MousePosition.Y > 985 && MousePosition.Y < 1000
                        && MousePosition.X < 200)
                        {
                            WindowStuff->DrawSubMenu(1);
                        }
                        else
                        {

                        }
                    }

                    break;
                
                default:
                    if (WindowStuff->SubMenuStatus == true)
                    {
                        if (MousePosition.Y > 620 && MousePosition.Y < 650
                        && MousePosition.X > 75 && MousePosition.X < 200)
                        {
                            Shutdown();
                        }
                        else if (MousePosition.Y > 651 && MousePosition.Y < 680
                        && MousePosition.X < 200)
                        {
                            Reboot();
                        }
                        else if (MousePosition.Y > 685 && MousePosition.Y < 700
                        && MousePosition.X < 200)
                        {
                            WindowStuff->DrawSubMenu(1);
                        }
                        else
                        {

                        }
                    }

                break;
            }
        }
        if (MousePacket[0] & PS2Middlebutton)
        {
            GlobalRenderer->Print((to_string(MousePosition.X)));
            GlobalRenderer->Print("|", 1);
            GlobalRenderer->Print((to_string(MousePosition.Y)));
            GlobalRenderer->Print(" ", 1);
        }

        if (MousePacket[0] & PS2Rightbutton)
        {
            if (MousePosition.Y >= WindowStuff->ResoHeight - 185 && MousePosition.Y <= WindowStuff->ResoHeight - 175)
            {
                if (WindowStuff->StartMenuStatus == true)
                {
                    if (MousePosition.X <= WindowStuff->ResoWidth - 1324)
                    {
                        WindowStuff->OpenApplication(1, 300, 300, 300, 300, 0xffcc0000);
                    }
                }
            }
            else
            {
                switch (WindowStuff->ResoWidth | WindowStuff->ResoHeight)
                {
                    case 1920 | 1080:
                        if (MousePosition.Y >= 925 && MousePosition.Y <= 935)
                        {
                            if (WindowStuff->StartMenuStatus == true)
                            {
                                if (MousePosition.X <= 42)
                                {
                                    WindowStuff->DrawSubMenu(2);
                                }
                            }
                        }
                        break;
                    
                    default:
                        if (MousePosition.Y >= 625 && MousePosition.Y <= 635)
                        {
                            if (WindowStuff->StartMenuStatus == true)
                            {
                                if (MousePosition.X <= 42)
                                {
                                    WindowStuff->DrawSubMenu(2);
                                }
                            }
                        }
                        break;
                }
            }
        }

        MousePacketReady = false;
        MousePositionOld = MousePosition;
    }
}

void Clear()
{
    GlobalRenderer->ClearMouseCursor(cursor, MousePositionOld);
}

void InitPS2Mouse()
{
 
    outb(0x64, 0xA8); //enabling the auxiliary device - mouse

    MouseWait();
    outb(0x64, 0x20); //tells the keyboard controller that we want to send a command to the mouse
    MouseWaitInput();
    uint8_t status = inb(0x60);
    status |= 0b10;
    MouseWait();
    outb(0x64, 0x60);
    MouseWait();
    outb(0x60, status); // setting the correct bit is the "compaq" status byte

    MouseWrite(0xF6);
    MouseRead();

    MouseWrite(0xF4);
    MouseRead();
}