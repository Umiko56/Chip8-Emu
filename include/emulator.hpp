#pragma once

#include <SDL2/SDL.h>
#include "memory.h"
#include "cpu.hpp"
#include "input.hpp"
#include "screen.hpp"

class Emulator
{
public:
    Emulator();
    void execute();
    void operator()();
    Cpu cpu;
    Input input;
    Screen screen;
};
