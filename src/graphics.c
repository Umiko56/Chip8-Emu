#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

void clear_screen(struct s_screen *screen)
{
    memset(screen->pixels, BLACK, sizeof(screen->pixels));
}

int initialize_screen(struct s_screen *screen)
{
    screen->w = SDL_CreateWindow("Emulateur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(NULL == screen->w)
    {
        fprintf(stderr, "Error SDL_CreateWindow: %s.\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    screen->r = SDL_CreateRenderer(screen->w, -1, SDL_RENDERER_ACCELERATED);
    if(NULL == screen->r)
    {
        fprintf(stderr, "Error SDL_CreateRenderer: %s.\n", SDL_GetError());
        SDL_DestroyWindow(screen->w);
        return EXIT_FAILURE;
    }
    clear_screen(screen);
    screen->pixel_height = PIXEL_DIM;
    screen->pixel_width = PIXEL_DIM;
    return EXIT_SUCCESS;
}

void destroy_screen(struct s_screen *screen)
{
    SDL_DestroyRenderer(screen->r);
    SDL_DestroyWindow(screen->w);
}

void update_screen(struct s_screen *screen)
{
    SDL_SetRenderDrawColor(screen->r, 0, 0, 0, 255);
    SDL_RenderClear(screen->r);
    SDL_SetRenderDrawColor(screen->r, 255, 255, 255, 255);
    for(size_t i = 0; i < PIXEL_BY_WIDTH; i++)
    {
        for(size_t j = 0; j < PIXEL_BY_HEIGHT; j++)
        {
            if(screen->pixels[i][j] == WHITE)
            {
                SDL_Rect pixel_rect = {
                    screen->pixel_width * i, screen->pixel_height * j,
                    screen->pixel_width, screen->pixel_height
                };
                SDL_RenderFillRect(screen->r, &pixel_rect);
            }
        }
    }
    SDL_RenderPresent(screen->r);
}
