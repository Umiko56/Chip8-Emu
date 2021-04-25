#include "input.hpp"
Input::Input() : quit(false)
{
}

void Input::execute(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = SDL_TRUE;
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                key[0x1] = 0;
                break;
            case SDLK_2:
                key[0x2] = 0;
                break;
            case SDLK_3:
                key[0x3] = 0;
                break;
            case SDLK_4:
                key[0xC] = 0;
                break;
            case SDLK_q:
                key[0x4] = 0;
                break;
            case SDLK_w:
                key[0x5] = 0;
                break;
            case SDLK_e:
                key[0x6] = 0;
                break;
            case SDLK_r:
                key[0xD] = 0;
                break;
            case SDLK_a:
                key[0x7] = 0;
                break;
            case SDLK_s:
                key[0x8] = 0;
                break;
            case SDLK_d:
                key[0x9] = 0;
                break;
            case SDLK_f:
                key[0xE] = 0;
                break;
            case SDLK_z:
                key[0xA] = 0;
                break;
            case SDLK_x:
                key[0x0] = 0;
                break;
            case SDLK_c:
                key[0xB] = 0;
                break;
            case SDLK_v:
                key[0xF] = 0;
                break;
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_1:
                key[0x1] = 1;
                break;
            case SDLK_2:
                key[0x2] = 1;
                break;
            case SDLK_3:
                key[0x3] = 1;
                break;
            case SDLK_4:
                key[0xC] = 1;
                break;
            case SDLK_q:
                key[0x4] = 1;
                break;
            case SDLK_w:
                key[0x5] = 1;
                break;
            case SDLK_e:
                key[0x6] = 1;
                break;
            case SDLK_r:
                key[0xD] = 1;
                break;
            case SDLK_a:
                key[0x7] = 1;
                break;
            case SDLK_s:
                key[0x8] = 1;
                break;
            case SDLK_d:
                key[0x9] = 1;
                break;
            case SDLK_f:
                key[0xE] = 1;
                break;
            case SDLK_z:
                key[0xA] = 1;
                break;
            case SDLK_x:
                key[0x0] = 1;
                break;
            case SDLK_c:
                key[0xB] = 1;
                break;
            case SDLK_v:
                key[0xF] = 1;
                break;
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
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
}
