#pragma once

#include <stdint.h>
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
    int xrel;
    int yrel;
    int xwheel, ywheel;
    bool mouse[6];
    bool resize;
};