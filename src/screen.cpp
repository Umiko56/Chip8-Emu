#include "screen.hpp"

Screen::Screen(void) : dirty(true), screen_height(32), screen_width(64)
{
    w = SDL_CreateWindow("Umiko is adorable!",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         screen_width * PIXEL_SIZE,
                         screen_height * PIXEL_SIZE,
                         SDL_WINDOW_SHOWN);
    SDL_Delay(1000);
    if (w == nullptr)
    {
        std::cerr << "Could not create SDL_Window instance!";
        return;
    }
    r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
    if (r == nullptr)
    {
        std::cerr << "Could not create SDL_Renderer instance!";
        SDL_DestroyWindow(w);
        return;
    }
    clear();
    return;
}

Screen::~Screen(void)
{
}

bool Screen::drawpx(uint8_t x, uint8_t y)
{
    x %= 64;
    y %= 32;
    screenbuffer[x + (y * screen_width)] = !screenbuffer[x + (y * screen_width)];
    return screenbuffer[x + (y * screen_width)];
}

bool Screen::readpx(uint8_t x, uint8_t y)
{
    return screenbuffer[x + (y * screen_width)];
}

void Screen::execute(void)
{
    if (dirty)
    {
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        for (int i = 0; i < screen_width; i++)
        {
            for (int j = 0; j < screen_height; j++)
            {
                if ((screenbuffer)[i + (j * screen_width)] == true)
                {
                    SDL_Rect pixel_rect = {
                        PIXEL_SIZE * i,
                        PIXEL_SIZE * j,
                        PIXEL_SIZE,
                        PIXEL_SIZE};
                    SDL_RenderFillRect(r, &pixel_rect);
                }
            }
        }
        SDL_RenderPresent(r);
        dirty = false;
    }
}

void Screen::clear()
{
    for (int x = 0; x < screen_width * screen_height; x++)
    {
        screenbuffer[x] = false;
    }
}
