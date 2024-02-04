#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include "Map.h"
#include "Util.h"
#include "ImageView.h"
#include <Player.h>


int main(int ac,char **argv)
{
    extern Player user,comp;
    extern int gameOver;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL_Error: %s",SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *win = SDL_CreateWindow("ClashedGame",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIN_WIDTH,WIN_HEIGHT,SDL_WINDOW_SHOWN);

    SDL_Renderer *ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event ev;

    InitGame(ren);
    
    while (running)
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_QUIT:
                    running = false;
                break;

                case (SDL_KEYDOWN):
                {
                    if (!gameOver){
                        char key = GetKeyPressed(ev.key);
                        if (key == 'r')
                        MoveMap(MAP_DIR_RIGHT);
                        if (key == 'u')
                        MoveMap(MAP_DIR_UP);
                        if (key == 'd')
                        MoveMap(MAP_DIR_DOWN);
                        if (key == 'l')
                        MoveMap(MAP_DIR_LEFT);
                        if(key == 's')
                        PlayerAttack(ren,&user,'u');
                    }
                }
                break;

                default:
                break;
            }
        }

        SDL_SetRenderDrawColor(ren,0,0,0,255);
        SDL_RenderClear(ren);

        if (gameOver)
        {
            GameOver(ren);
        }else{
            RenderMap(ren);
        }
        SDL_RenderPresent(ren);
        SDL_Delay(17);
    }

    DestroyMap();
    SDL_Quit();
    return (EXIT_SUCCESS);
}