#include "ImageView.h"


SDL_Texture* LoadImage(const char *path,SDL_Renderer *ren)
{
    SDL_Surface* imgSf = IMG_Load(path);
    SDL_Texture* imgTx = SDL_CreateTextureFromSurface(ren,imgSf);

    return imgTx;
}

ImageView* CreateImageView(const char *path,SDL_Renderer *ren,SDL_Rect *imgRect,SDL_Rect *dstRect)
{
    ImageView *imgV = (ImageView*)malloc(sizeof(ImageView));
    imgV->path = path;
    imgV->imgTx = LoadImage(path,ren);

    imgV->srcRect = imgRect;
    imgV->dstRect = dstRect;
    return imgV;
}

void RenderImageView(SDL_Renderer *ren,ImageView *iv)
{
    SDL_RenderCopy(ren,iv->imgTx,iv->srcRect,iv->dstRect);
}

void DeleteImageView(ImageView* imgV)
{
    SDL_DestroyTexture(imgV->imgTx);
    free(imgV);
}
