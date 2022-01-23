#pragma once

#include <stdint.h>

#include "../BasicRenderer.hpp"

class Shell
{
    public:
        long shellheight;
        long shellwidth;
        long shellx;
        long shelly;

        void ShellInit();
};

extern Shell* ShellStuff;