#include "input.hpp"
Input::Input() : quit(false)
{
}

void Input::execute(void)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        quit = SDL_TRUE;
        break;

    case SDL_KEYDOWN:
        key[event.key.keysym.scancode] = SDL_TRUE;
        break;

    case SDL_KEYUP:
        key[event.key.keysym.scancode] = SDL_FALSE;
        break;

    case SDL_MOUSEMOTION:
        x = event.motion.x;
        y = event.motion.y;
        xrel = event.motion.xrel;
        yrel = event.motion.yrel;
        break;

    case SDL_MOUSEWHEEL:
        xwheel = event.wheel.x;
        ywheel = event.wheel.y;
        break;

    case SDL_MOUSEBUTTONDOWN:
        mouse[event.button.button] = SDL_TRUE;
        break;

    case SDL_MOUSEBUTTONUP:
        mouse[event.button.button] = SDL_FALSE;
        break;

    case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            resize = SDL_TRUE;
        }
        break;
    default:
        break;
    }
}
