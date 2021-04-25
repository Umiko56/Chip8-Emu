#pragma once

#include <SDL2/SDL.h>
#include "memory.h"
#include "cpu.hpp"
#include "input.hpp"
#include "screen.hpp"

class Emulator
{
public:
    Emulator(char *path);
    void execute();
    Input input;
    Screen screen;
    Cpu cpu;
};

extern Emulator *emulator;
