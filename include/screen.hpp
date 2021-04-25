#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

#define PIXEL_SIZE 16

class Screen
{
public:
    Screen();
    ~Screen();
    void drawpx(uint8_t x, uint8_t y, bool value);
    bool readpx(uint8_t x, uint8_t y);
    void execute(void);
    void clear();

private:
    SDL_Window *w;
    SDL_Renderer *r;
    bool screenbuffer[64 * 32];
    uint16_t screen_height;
    uint16_t screen_width;
};