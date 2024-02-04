#ifndef CL_OBS
#define CL_OBS

#include <SDL2/SDL_render.h>
#include <ImageView.h>

#define OBS_KIND_CHAIR "./img/chair.png"
#define OBS_KIND_TABLE "./img/table.png"
#define OBS_KIND_FISH "./img/fishBowl.png"

typedef struct obstacle {
    ImageView *iv;
    SDL_Rect rect;
}Obstacle;

Obstacle* CreateObstacle(SDL_Renderer *ren,SDL_Rect pos,const char *kind);
void RenderObstacle(SDL_Renderer *ren,Obstacle *obs);
void DestroyObstacle(Obstacle *obs);

#endif