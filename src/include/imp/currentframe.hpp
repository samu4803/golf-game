#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include"imp/background.hpp"
SDL_Renderer *render;
class frame
{
  public:
  void clear();
  void present();
  void copy(SDL_Texture* texture,int x,int y,int m, int n);
  void renderer(SDL_Renderer *ren);
  void lock(SDL_Renderer *ren,SDL_Texture *texture);
  void copy(SDL_Texture* texture);
  private:

  SDL_Texture *background;
  
  SDL_Rect srect,drect;
};
void frame::clear()
{
  SDL_RenderClear(render);
}
void frame::present()
{
  SDL_RenderPresent(render);
}
void frame::copy(SDL_Texture* texture,int x,int y,int m,int n)
{
    drect.x=m;
    drect.y=n;
    drect.w=x;
    drect.h=y;
    srect.x=0;
    srect.y=0;
    srect.w=x;
    srect.h=y;
    show(); // making background
  SDL_RenderCopy(render,texture,&srect,&drect);
}
void frame::copy(SDL_Texture* texture)
{
  SDL_RenderCopy(render,texture,NULL,NULL);
}
void frame::renderer(SDL_Renderer* ren)
{
  render=ren;
}
void frame::lock(SDL_Renderer *ren,SDL_Texture *texture)
{
  //SDL_LockTexture(texture,&drect,21*21,21);
}
