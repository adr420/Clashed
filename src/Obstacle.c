#include <Obstacle.h>

Obstacle* CreateObstacle(SDL_Renderer *ren, SDL_Rect pos,const char* kind)
{
    Obstacle *obs = (Obstacle*)malloc(sizeof(Obstacle));
    obs->rect = pos;
    obs->iv = CreateImageView(kind,ren,NULL,&obs->rect);

    return obs;
}

void RenderObstacle(SDL_Renderer *ren,Obstacle *obs)
{
    RenderImageView(ren,obs->iv);
}

void DestroyObstacle(Obstacle *obs)
{
    DeleteImageView(obs->iv);
    free(obs);
}