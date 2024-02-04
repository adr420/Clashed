#include "Player.h"
#include "Map.h"
#include <Util.h>
#include <stdlib.h>

Player user;
Player comp;
Attack *attacks[1024];
int attackCount = 0;


void InitPlayers(SDL_Renderer *ren)
{
    //user init
    user.rect = (SDL_Rect){
        .x = 200,
        .y = 200,
        .w = 100,
        .h = 100
    };
    user.dir = PLAYER_DIR_RIGHT;
    user.imgs[0] = CreateImageView("./img/pl_left.png",ren,NULL,&user.rect);
    user.imgs[1] = CreateImageView("./img/pl_right.png",ren,NULL,&user.rect);
    user.imgs[2] = CreateImageView("./img/pl_down.png",ren,NULL,&user.rect);
    user.imgs[3] = CreateImageView("./img/pl_up.png",ren,NULL,&user.rect);

    // computer init
    comp.rect = (SDL_Rect){
        .x = rand()%1024,
        .y = rand()%1024,
        .w = 100,
        .h = 100
    };
    comp.dir = PLAYER_DIR_DOWN;
    comp.imgs[0] = CreateImageView("./img/cmp_left.png",ren,NULL,&comp.rect);
    comp.imgs[1] = CreateImageView("./img/cmp_right.png",ren,NULL,&comp.rect);
    comp.imgs[2] = CreateImageView("./img/cmp_down.png",ren,NULL,&comp.rect);
    comp.imgs[3] = CreateImageView("./img/cmp_up.png",ren,NULL,&comp.rect);
}


void PlayerAttack(SDL_Renderer *ren,Player *p,char attacker)
{

    attacks[attackCount] = (Attack*)malloc((sizeof(Attack)));
    attacks[attackCount]->rect = p->rect;
    attacks[attackCount]->rect.w = attacks[attackCount]->rect.h = 50;
    attacks[attackCount]->dir = p->dir;
    attacks[attackCount]->attacker = attacker;

    if (p->dir == PLAYER_DIR_LEFT)
    {
        attacks[attackCount]->rect.x -= 25;
        attacks[attackCount]->rect.y += p->rect.h/2;
    }
    if (p->dir == PLAYER_DIR_RIGHT)
    {
        attacks[attackCount]->rect.x += 25;
        attacks[attackCount]->rect.y += p->rect.h/2;
    }
    if (p->dir == PLAYER_DIR_UP)
    {
        attacks[attackCount]->rect.y -= 25;
        attacks[attackCount]->rect.x += p->rect.w/4;
    }
    if (p->dir == PLAYER_DIR_DOWN)
    {
        attacks[attackCount]->rect.y += 25;
        attacks[attackCount]->rect.x += p->rect.w/4;
    }

    if (attacker == 'u')
    {
        attacks[attackCount]->imgs[0] = CreateImageView("./img/pl_attack_left.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[1] = CreateImageView("./img/pl_attack_right.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[2] = CreateImageView("./img/pl_attack_down.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[3] = CreateImageView("./img/pl_attack_up.png",ren,NULL,&attacks[attackCount]->rect);
    }else if (attacker == 'c'){
        attacks[attackCount]->imgs[0] = CreateImageView("./img/cmp_attack_left.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[1] = CreateImageView("./img/cmp_attack_right.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[2] = CreateImageView("./img/cmp_attack_down.png",ren,NULL,&attacks[attackCount]->rect);
        attacks[attackCount]->imgs[3] = CreateImageView("./img/cmp_attack_up.png",ren,NULL,&attacks[attackCount]->rect);
    }
    attackCount++;
}

int isInRect(SDL_Rect atk,SDL_Rect pl)
{
    if ((atk.x >= pl.x && atk.x <= pl.x + pl.w)
        &&
        (atk.y >= pl.y && atk.y <= pl.y + pl.h))
        return 1;

    return 0;
}

void RenderAttacks(SDL_Renderer *ren)
{
    extern const char *over_text;

    for (int i = 0; i<attackCount; i++)
    {
        RenderImageView(ren,attacks[i]->imgs[attacks[i]->dir]);
        
        if (isInRect(attacks[i]->rect,user.rect) && attacks[i]->attacker != 'u')
        {
            DestroyAttack(i);
            if (i > 0)
            i--;
            over_text = "You Lost!";
            GameOver(ren);
        }

        if (isInRect(attacks[i]->rect,comp.rect) && attacks[i]->attacker != 'c')
        {
            DestroyAttack(i);
            if (i > 0)
            i--;
            over_text = "You Won!";
            GameOver(ren);
        }

        if (attacks[i]->dir == ATTACK_DIR_LEFT)
        {
            attacks[i]->rect.x -= 10;

            if (attacks[i]->rect.x + attacks[i]->rect.w < 0)
            {
                DestroyAttack(i);

                if (i > 0)
                i--;
            }
        }else if (attacks[i]->dir == ATTACK_DIR_RIGHT)
        {
            attacks[i]->rect.x += 10;

            if (attacks[i]->rect.x > 4 * 1024)
            {
                DestroyAttack(i);
                if (i > 0)
                i--;
            }
        }else if (attacks[i]->dir == ATTACK_DIR_UP)
        {
            attacks[i]->rect.y -= 10;

            if (attacks[i]->rect.y + attacks[i]->rect.h < 0)
            {
                DestroyAttack(i);
                if (i > 0)
                i--;
            }
        }else if (attacks[i]->dir == ATTACK_DIR_DOWN)
        {
            attacks[i]->rect.y += 10;

            if (attacks[i]->rect.y > 4 * 1024)
            {
                DestroyAttack(i);
                if (i > 0)
                i--;
            }
        }
    }
}

void DestroyAttack(int i)
{
    Attack *a = attacks[i];

    for (int k=i; k<attackCount-1; k++)
    {
        attacks[k] = attacks[k+1];
    }

    attackCount--;

    DeleteImageView(a->imgs[0]);
    DeleteImageView(a->imgs[1]);
    DeleteImageView(a->imgs[2]);
    DeleteImageView(a->imgs[3]);
    free(a);
}


void PlayComputer(SDL_Renderer *ren)
{
    int diffX = user.rect.x - comp.rect.x;
    int diffY = user.rect.y - comp.rect.y;

    int usr_rel_dirX = -1;
    int usr_rel_dirY = -1;
    int moveSpeed = 8;

    if (diffX <= -20)
    {
        usr_rel_dirX = PLAYER_DIR_LEFT;
        comp.rect.x -= rand() % 4;
        comp.dir = usr_rel_dirX;
    }else if (diffX > 50){
        usr_rel_dirX = PLAYER_DIR_RIGHT;
        comp.rect.x += rand() % 4;
        comp.dir = usr_rel_dirX;
    }else if (diffY <= 0)
    {
        usr_rel_dirY = PLAYER_DIR_UP;
        comp.rect.y -= rand() % 4;
        comp.dir = usr_rel_dirY;

    }else {
        usr_rel_dirY = PLAYER_DIR_DOWN;
        comp.rect.y += rand() % 4;
        comp.dir = usr_rel_dirY;
    }

    if (rand() % 40 == 27)
    PlayerAttack(ren,&comp,'c');

}

void RenderPlayers(SDL_Renderer *ren)
{
    RenderAttacks(ren);
    // Stimulating the computer
    PlayComputer(ren);
    RenderImageView(ren,user.imgs[user.dir]);
    RenderImageView(ren,comp.imgs[comp.dir]);
}

