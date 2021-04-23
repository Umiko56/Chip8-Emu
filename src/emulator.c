#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "graphics.h"
#include "emulator.h"

void update_event(struct s_input *input)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            input->quit = SDL_TRUE;
            break;

        case SDL_KEYDOWN:
            input->key[event.key.keysym.scancode] = SDL_TRUE;
            break;

        case SDL_KEYUP:
            input->key[event.key.keysym.scancode] = SDL_FALSE;
            break;

        case SDL_MOUSEMOTION:
            input->x = event.motion.x;
            input->y = event.motion.y;
            input->xrel = event.motion.xrel;
            input->yrel = event.motion.yrel;
            break;

        case SDL_MOUSEWHEEL:
            input->xwheel = event.wheel.x;
            input->ywheel = event.wheel.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            input->mouse[event.button.button] = SDL_TRUE;
            break;

        case SDL_MOUSEBUTTONUP:
            input->mouse[event.button.button] = SDL_FALSE;
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                input->resize = SDL_TRUE;
            }
            break;

        }
    }
}

int initialize_SDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Error SDL_Init: %s.\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void destroy_SDL(void)
{
    SDL_Quit();
}

int initialize_emulator(struct s_emulator *emulator)
{
    int status = -1;
    initialize_cpu(&emulator->cpu);
    memset(&emulator->in, 0, sizeof(emulator->in));
    if (0 == initialize_SDL())
    {
        int status = initialize_screen(&emulator->screen);
        if (0 > status)
            destroy_SDL();
    }
    return status;
}

void destroy_emulator(struct s_emulator *emulator)
{
    destroy_screen(&emulator->screen);
    destroy_SDL();
}

void emulate(struct s_emulator *emulator)
{
    while (!emulator->in.quit)
    {
        update_event(&emulator->in);
        update_screen(&emulator->screen);
        SDL_Delay(20);
    }
}
