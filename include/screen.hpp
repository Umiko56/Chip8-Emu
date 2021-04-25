#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include <iostream>

#define PIXEL_SIZE 16

class Screen
{
public:
    Screen();
    ~Screen();
    bool drawpx(uint8_t x, uint8_t y);
    bool readpx(uint8_t x, uint8_t y);
    void execute(void);
    void clear();
    bool dirty;

private:
    SDL_Window *w;
    SDL_Renderer *r;
    bool screenbuffer[64 * 32];
    uint16_t screen_height;
    uint16_t screen_width;
};