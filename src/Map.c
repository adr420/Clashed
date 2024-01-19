#include "Map.h"

Map gameMap;

void InitMap(SDL_Renderer *ren)
{
    
    gameMap.bg = CreateImageView("./img/playground27m.png", ren, (SDL_Rect){.x = 0, .y = 0, .w = 200, .h = 200}, (SDL_Rect){0, 0, WIN_WIDTH, WIN_HEIGHT});

}

void RenderMap(SDL_Renderer *ren)
{
    RenderImageView(ren, gameMap.bg);
}

void MoveMap(int dir)
{
    int moveSpeed = 4;
    if (dir == MAP_DIR_LEFT)
    {
        if (gameMap.bg->srcRect.x - moveSpeed >= 0)
        gameMap.bg->srcRect.x -= moveSpeed;
    }else if (dir == MAP_DIR_RIGHT)
    {
        if (gameMap.bg->srcRect.x + moveSpeed <= WIN_WIDTH)
        gameMap.bg->srcRect.x += moveSpeed;
    }else if (dir == MAP_DIR_DOWN)
    {
        if (gameMap.bg->srcRect.y + moveSpeed <= WIN_HEIGHT)
        gameMap.bg->srcRect.y += moveSpeed;
    }else if (dir == MAP_DIR_UP)
    {
        if (gameMap.bg->srcRect.y - moveSpeed >= 0)
        gameMap.bg->srcRect.y -= moveSpeed;
    }
}

void DestroyMap()
{
    DeleteImageView(gameMap.bg);
}
