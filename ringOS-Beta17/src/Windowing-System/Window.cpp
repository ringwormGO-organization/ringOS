#include "Window.h"

namespace Window
{
    void DrawTerminal(uint32_t color)
    {
        for (int y = 600; y < 1000; y++)
        {
            for (int x = 600; x < 1000; x++)
            {
                GlobalRenderer->PutPix(x, y, color);
            }
        }
        
    }
}