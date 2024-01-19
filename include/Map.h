#ifndef CL_MAP
#define CL_MAP


#include <SDL2/SDL_render.h>
#include <ImageView.h>
#include <Util.h>

#define MAP_DIR_LEFT 0
#define MAP_DIR_RIGHT 1
#define MAP_DIR_UP 2
#define MAP_DIR_DOWN 3

typedef struct map
{
    ImageView *bg;
} Map;


void InitMap(SDL_Renderer *ren);
void RenderMap(SDL_Renderer *ren);
void MoveMap(int dir);
void DestroyMap();



#endif