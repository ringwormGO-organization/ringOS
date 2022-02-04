#pragma once

#include <stdint.h>

#include "../BasicRenderer.hpp"
#include "../library/string.hpp"

class Shell
{
    public:
        long shellheight;
        long shellwidth;
        long shellx;
        long shelly;

        void ShellInit();
        void Command();
};

extern Shell* ShellStuff;