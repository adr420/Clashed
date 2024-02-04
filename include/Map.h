#ifndef CL_MAP
#define CL_MAP


#include <SDL2/SDL_render.h>
#include <ImageView.h>
#include <Util.h>
#include <Player.h>
#include <Obstacle.h>

#define MAP_DIR_LEFT 0
#define MAP_DIR_RIGHT 1
#define MAP_DIR_UP 2
#define MAP_DIR_DOWN 3

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024
#define OBS_CNT 80

typedef struct map
{
    ImageView *bg;
    SDL_Rect mapRect;
    SDL_Rect screenRect;
    Player *userP;
    Player *compP;
    Obstacle *obs[OBS_CNT];
} Map;


void InitMap(SDL_Renderer *ren);
void RenderMap(SDL_Renderer *ren);
void MoveMap(int dir);
void MoveObjects(int moveSpeedX,int moveSpeedY);
void DestroyMap();


#endif