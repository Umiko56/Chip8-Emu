#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

#define BLACK SDL_FALSE
#define WHITE SDL_TRUE
#define PIXEL_BY_WIDTH 64
#define PIXEL_BY_HEIGHT 32
#define PIXEL_DIM 8
#define WIDTH  PIXEL_BY_WIDTH*PIXEL_DIM 
#define HEIGHT PIXEL_BY_HEIGHT*PIXEL_DIM

typedef SDL_bool s_pixel;

struct s_screen
{
    SDL_Window *w;
    SDL_Renderer *r;
    s_pixel pixels[PIXEL_BY_WIDTH][PIXEL_BY_HEIGHT];
    uint32_t pixel_height;
    uint32_t pixel_width;
};

void clear_screen(struct s_screen *screen);
int initialize_screen(struct s_screen *screen);
void destroy_screen(struct s_screen *screen);

void update_screen(struct s_screen *screen);
