#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include <iostream>

class Input
{
public:
    Input();
    void execute(void);
    bool key[16];
    bool quit;
    int x;
    int y;
    bool resize;
};