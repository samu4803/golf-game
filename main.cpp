#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"imp/currentframe.hpp" 
#include"imp/ball.hpp"
#include"imp/background.hpp"
void loadlevel();
int level =1;
int main(int argc,char* args[])
{
    float goleX,goleY;
    int level;
   // ShowWindow()
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window=SDL_CreateWindow("Golf Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,500,500,SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *render=SDL_CreateRenderer(window,-1,SDL_RENDERER_TARGETTEXTURE);
    SDL_Surface *icon=IMG_Load("src\\res\\untitled.png");
    SDL_SetWindowIcon(window,icon);
    SDL_FreeSurface(icon);
    frame currentframe;
    int test=0;
    SDL_Texture *Ball=IMG_LoadTexture(render,"src\\res\\ball.xcf");  
    SDL_Event event;
    bool GameRunning=true;
    ballAI mball;
    SDL_Rect screen;
    currentframe.renderer(render);
    ground(render);
    frames(240,100,21,21);
    mball.destination(240.00,100.00);
    while(GameRunning==true)
    {
        SDL_Delay(10);

        currentframe.clear();
        currentframe.copy(Ball,16,16,mball.giveX(),mball.giveY());
        SDL_RenderPresent(render);

        if(SDL_PollEvent(&event))
        {
            SDL_Delay(10);
            switch(event.type)
            {
                case(SDL_MOUSEBUTTONUP):
                mball.move(mball.giveX(),mball.giveY(),event.motion.x,event.motion.y,render,Ball);
                std::cout<<"\nmouse X="<<event.motion.x<<"\n mouse Y="<<event.motion.y;
                break;
                case(SDL_QUIT):
                GameRunning=false;
                break;
                //default:
               // test=0;
            }
        }
    }
    SDL_DestroyTexture(Ball);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



