#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

#define PIXEL_SIZE 4

class Screen
{
public:
    Screen();
    ~Screen();
    void drawpx(uint8_t x, uint8_t y, bool value);
    void execute(void);
    void operator()();
    void clear();

private:
    SDL_Window *w;
    SDL_Renderer *r;
    bool screenbuffer[64 * 32];
    uint16_t screen_height;
    uint16_t screen_width;
};