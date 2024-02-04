#ifndef CL_PLYR
#define CL_PLYR

#include <SDL2/SDL.h>
#include <ImageView.h>


#define PLAYER_DIR_LEFT 0
#define PLAYER_DIR_RIGHT 1
#define PLAYER_DIR_DOWN 2
#define PLAYER_DIR_UP 3


#define ATTACK_DIR_LEFT 0
#define ATTACK_DIR_RIGHT 1
#define ATTACK_DIR_DOWN 2
#define ATTACK_DIR_UP 3


typedef struct player{
    ImageView *imgs[4];
    SDL_Rect rect;
    int dir;
}Player;

typedef struct attack{
    ImageView *imgs[4];
    SDL_Rect rect;
    int dir;
    char attacker;
}Attack;

void InitPlayers(SDL_Renderer *ren);
void PlayerAttack(SDL_Renderer *ren,Player *p,char attacker);
int isInRect(SDL_Rect atk,SDL_Rect pl);
void RenderAttacks(SDL_Renderer *ren);
void DestroyAttack(int i);
void PlayComputer(SDL_Renderer *ren);
void RenderPlayers(SDL_Renderer *ren);

#endif