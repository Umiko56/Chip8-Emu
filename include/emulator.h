#pragma once

#include <SDL2/SDL.h>
#include "memory.h"
#include "graphics.h"

struct s_emulator;
struct s_input;
void update_event(struct s_input *input);


struct s_input
{
    SDL_bool key[SDL_NUM_SCANCODES];
    SDL_bool quit;
    int x;
    int y;
    int xrel;
    int yrel;
    int xwheel, ywheel;
    SDL_bool mouse[6];
    SDL_bool resize;
};

struct s_emulator
{
    struct s_cpu cpu;
    struct s_screen screen;
    struct s_input in;
};


int initialize_SDL(void);
void destroy_SDL(void);
int initialize_emulator(struct s_emulator *emulator);
void destroy_emulator(struct s_emulator *emulator);
void emulate(struct s_emulator *emulator);