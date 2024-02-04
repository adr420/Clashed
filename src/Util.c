#include "Util.h"
#include <SDL2/SDL_ttf.h>
#include <Player.h>

int gameOver = 0;
const char *over_text = "";
void InitGame(SDL_Renderer *ren)
{
    InitMap(ren);
    InitPlayers(ren);
}

int nextColl(SDL_Rect usr,SDL_Rect obs, float del,int usrDir)
{
    if (usrDir == PLAYER_DIR_LEFT)
    {
        if ((obs.x <= usr.x && obs.x + obs.w >= usr.x)
            &&
            ((obs.y >= usr.y && obs.y <= usr.y + usr.h) 
            ||
            (obs.y + obs.h >= usr.y && obs.y + obs.h <= usr.y + usr.h)))
            return 1;
    }
    else if (usrDir == PLAYER_DIR_RIGHT)
    {
        if ((obs.x <= usr.x + usr.w && obs.x + obs.w >= usr.x + usr.w)
            &&
            ((obs.y >= usr.y && obs.y <= usr.y + usr.h) 
            ||
            (obs.y + obs.h >= usr.y && obs.y + obs.h <= usr.y + usr.h)))
            return 1;
    }else if (usrDir == PLAYER_DIR_UP)
    {
        if ((obs.y <= usr.y && obs.y + obs.h >= usr.y)
            &&
            ((obs.x >= usr.x && obs.x <= usr.x + usr.w) 
            ||
            (obs.x + obs.w >= usr.x && obs.x + obs.w <= usr.x + usr.w)))
            return 1;
    }
    else if (usrDir == PLAYER_DIR_DOWN)
    {
        if ((obs.y <= usr.y + usr.h && obs.y + obs.h >= usr.y + usr.h)
            &&
            ((obs.x >= usr.x && obs.x <= usr.x + usr.w) 
            ||
            (obs.x + obs.w >= usr.x && obs.x + obs.w <= usr.x + usr.w)))
            return 1;
    }
    return 0;
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

SDL_Texture* LoadText(SDL_Renderer *ren,const char *text)
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./font/gameFont.ttf",256);

    SDL_Color color = {255,255,255};
    SDL_Surface *surface = TTF_RenderText_Solid(font,text,color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren,surface);

    return texture;
}


void GameOver(SDL_Renderer *ren)
{
    extern int gameOver;
    extern const char *over_text;
    static SDL_Texture *txt;
    SDL_Rect rect = {100,100,600,150};

    gameOver = 1;

    if (gameOver == 1){
        txt = LoadText(ren,over_text);
        gameOver = 2;
    }

    SDL_RenderCopy(ren,txt,NULL,&rect);

}