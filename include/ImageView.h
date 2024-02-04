#ifndef CL_IMAGE_VIEW
#define CL_IMAGE_VIEW

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

typedef struct image_view {
    const char *path;
    SDL_Texture *imgTx;
    SDL_Rect *srcRect;
    SDL_Rect *dstRect;
}ImageView;

SDL_Texture* LoadImage(const char *path,SDL_Renderer *ren);

ImageView* CreateImageView(const char *path,SDL_Renderer *ren,SDL_Rect *imgRect,SDL_Rect *dstRect);

void RenderImageView(SDL_Renderer *ren,ImageView *iv);

void DeleteImageView(ImageView* imgV);

#endif