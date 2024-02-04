#ifndef CL_UTIL
#define CL_UTIL

#define WIN_WIDTH 800
#define WIN_HEIGHT 800

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <Map.h>

void InitGame(SDL_Renderer *ren);
char GetKeyPressed(SDL_KeyboardEvent key);
int nextColl(SDL_Rect r,SDL_Rect within,float del,int usrDir);
void GameOver(SDL_Renderer *ren);

#endif