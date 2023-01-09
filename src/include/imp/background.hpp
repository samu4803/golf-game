#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
SDL_Renderer *ren;
SDL_Texture *golf_background;
SDL_Texture *goal;
SDL_Rect srect, drect;

void ground(SDL_Renderer *render)
{
    ren = render;
    golf_background = IMG_LoadTexture(render, "src\\res\\ground.png");
    goal = IMG_LoadTexture(render, "src\\res\\hole.png");
}
void show()
{

    SDL_RenderCopy(ren, golf_background, NULL, NULL);
    SDL_RenderCopy(ren, goal, NULL, &drect);
}
void frames(int x, int y, int w, int h)
{
    drect.x = x;
    drect.y = y;
    drect.w = w;
    drect.h = h;
}
void clear()
{
    SDL_RenderClear(ren);
}