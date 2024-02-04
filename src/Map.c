#include "Map.h"
#include <Player.h>
#include <Obstacle.h>
#include <stdlib.h>
#include <time.h>

Map gameMap;

void InitMap(SDL_Renderer *ren)
{
    extern Player user;
    extern Player comp;

    gameMap.screenRect = (SDL_Rect){0, 0, WIN_WIDTH, WIN_HEIGHT};
    gameMap.mapRect = (SDL_Rect){.x = 0, .y = 0, .w = 200, .h = 200};

    gameMap.bg = CreateImageView("./img/playground27m.png", ren, &gameMap.mapRect, &gameMap.screenRect);
    gameMap.compP = &comp;
    gameMap.userP = &user;

    srand(time(NULL));

    const char *arr_obs[] = {OBS_KIND_CHAIR,OBS_KIND_TABLE};

    for (int i = 0; i < OBS_CNT; i++)
    {
        int maxx = 4*1024 - 100;
        int maxy = 4*1024 - 100;
        gameMap.obs[i] = CreateObstacle(ren,(SDL_Rect){
            rand()%maxx,
            rand()%maxy,
            100,
            100},arr_obs[rand()%2]);
    }
    
}


void RenderMap(SDL_Renderer *ren)
{
    RenderImageView(ren, gameMap.bg);    
    RenderPlayers(ren);
    for (int i = 0; i < OBS_CNT; i++)
    {
        RenderObstacle(ren,gameMap.obs[i]);
    }
}

void MoveMap(int dir)
{
    int moveSpeed = 4;
    
    if (dir == MAP_DIR_LEFT)
    {
        if (gameMap.mapRect.x - moveSpeed >= 0)
        {
            gameMap.userP->dir = PLAYER_DIR_LEFT;
            MoveObjects(moveSpeed,0);
        }
    }else if (dir == MAP_DIR_RIGHT)
    {
        if (gameMap.mapRect.x + moveSpeed <= WIN_WIDTH)
        {
            gameMap.userP->dir = PLAYER_DIR_RIGHT;
            MoveObjects(-moveSpeed,0);
        }
    }else if (dir == MAP_DIR_DOWN)
    {
        if (gameMap.mapRect.y + moveSpeed <= WIN_HEIGHT)
        {
            gameMap.userP->dir = PLAYER_DIR_DOWN;
            MoveObjects(0,-moveSpeed);
        }
    }else if (dir == MAP_DIR_UP)
    {
        if (gameMap.mapRect.y - moveSpeed >= 0)
        {
            gameMap.userP->dir = PLAYER_DIR_UP;
            MoveObjects(0,moveSpeed);
        }
    }
}

void MoveObjects(int moveSpeedX,int moveSpeedY)
{
    float v = (float)moveSpeedY/gameMap.mapRect.h;
    v *= WIN_HEIGHT;

    float h = (float)moveSpeedX/gameMap.mapRect.w;
    h *= WIN_WIDTH;
    

    SDL_Rect userR = gameMap.userP->rect;
    SDL_Rect compR = gameMap.compP->rect;

    if (!moveSpeedX && nextColl(userR,compR,h,gameMap.userP->dir))
        return;
    
    if (!moveSpeedY && nextColl(userR,compR,v,gameMap.userP->dir))
        return;

    for (int i = 0; i < OBS_CNT; i++)
    {
        if (!moveSpeedX && nextColl(userR,gameMap.obs[i]->rect,h,gameMap.userP->dir))
            return;
    
        if (!moveSpeedY && nextColl(userR,gameMap.obs[i]->rect,v,gameMap.userP->dir))
            return;
    }



    gameMap.mapRect.x -= moveSpeedX;
    gameMap.mapRect.y -= moveSpeedY;

    gameMap.compP->rect.x += h;
    gameMap.compP->rect.y += v;

    for (int i = 0; i < OBS_CNT; i++)
    {
        gameMap.obs[i]->rect.x += h;
        gameMap.obs[i]->rect.y += v;
    }
}

void DestroyMap()
{
    DeleteImageView(gameMap.bg);
}