#include "Util.h"

void InitGame(SDL_Renderer *ren)
{
    InitMap(ren);
}

char GetKeyPressed(SDL_KeyboardEvent key)
{
    if (key.keysym.sym == SDLK_UP)
    {
        return 'u';
    }else if (key.keysym.sym == SDLK_DOWN)
    {
        return 'd';
    }else if (key.keysym.sym == SDLK_RIGHT)
    {
        return 'r';
    }else if (key.keysym.sym == SDLK_LEFT)
    {
        return 'l';
    }else if(key.keysym.sym == SDLK_SPACE)
    {
        return 's';
    }

    return '\0';
}