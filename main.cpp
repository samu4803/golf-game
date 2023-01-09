#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "imp/currentframe.hpp"
#include "imp/ball.hpp"
#include "imp/background.hpp"
bool MainScreen(bool gamerunning, SDL_Event event);
bool Level(bool gamerunning, SDL_Event event);
bool nextlevelscreen(bool gamerunning, SDL_Event event);

int main(int argc, char *args[])
{
    float goleX, goleY;
    // creating windows

    SDL_Window *window = SDL_CreateWindow("Golf Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_ALLOW_HIGHDPI);

    // creating renderer

    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    // creating surface

    SDL_Surface *icon = IMG_Load("src\\res\\untitled.png");

    // setting windows icon

    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    frame currentframe;
    currentframe.renderer(render);
    ground(render);
    frames(240, 100, 21, 21);

    SDL_Event event;
    SDL_Rect screen;
    bool GameRunning = true;

    GameRunning = MainScreen(GameRunning, event);
    GameRunning = Level(GameRunning, event);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
bool MainScreen(bool gamerunning, SDL_Event event)
{
    SDL_Texture *play = IMG_LoadTexture(render, "src\\res\\play_button.png");
    SDL_Rect button;
    button.x = 250 - 45;
    button.y = 250 - 25;
    button.h = 50;
    button.w = 90;
    SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderCopy(render, play, NULL, &button);
    SDL_RenderPresent(render);
    bool thiswindow = true;
    while (gamerunning == true && thiswindow == true)
    {
        SDL_Delay(10);
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gamerunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x > 250 - 45 && event.motion.x < 350 - 45)
                {
                    if (event.motion.y > 250 - 25 && event.motion.y < 300 - 25)
                    {
                        thiswindow = false;
                    }
                }
            }
        }
    }

    return gamerunning;
}
bool nextlevelscreen(bool gamerunning, SDL_Event event)
{
    SDL_Texture *play = IMG_LoadTexture(render, "src\\res\\nxtlvl_button.png");
    SDL_Rect button;
    button.x = 250 - 45;
    button.y = 250 - 25;
    button.h = 50;
    button.w = 150;
    SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderCopy(render, play, NULL, &button);
    SDL_RenderPresent(render);
    bool thiswindow = true;
    while (gamerunning == true && thiswindow == true)
    {
        SDL_Delay(10);
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gamerunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.motion.x > 250 - 45 && event.motion.x < 350 - 45)
                {
                    if (event.motion.y > 250 - 25 && event.motion.y < 300 - 25)
                    {
                        thiswindow = false;
                    }
                }
            }
        }
    }
    return gamerunning;
}
bool Level(bool gamerunning, SDL_Event event)
{
    bool ThisWindow = true;
    int level = 0;

    SDL_Rect srect, drect;
    SDL_Texture *Ball = IMG_LoadTexture(render, "src\\res\\ball.xcf");
    ballAI mball;
    frame currentframe;

chooselevel:

    switch (level)
    {
    case (0):
        SDL_RenderClear(render);
        clear();
        frames(240, 100, 21, 21);
        mball.destination(240.00, 100.00);
        mball.getX(242.00);
        mball.getY(242.00);
        show();
        currentframe.copy(Ball, 16, 16, 242, 242);
        SDL_RenderPresent(render);
        break;
    case (1):
        SDL_RenderClear(render);
        clear();
        frames(100, 50, 21, 21);
        mball.destination(100.00, 50.00);
        mball.getX(200.00);
        mball.getY(100.00);
        show();
        currentframe.copy(Ball, 16, 16, 200, 100);
        SDL_RenderPresent(render);
        break;
    default:
        ThisWindow = false;
        break;
    }

    while (gamerunning == true && ThisWindow == true)
    {
        SDL_Delay(10);
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gamerunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mball.move(mball.giveX(), mball.giveY(), event.motion.x, event.motion.y, render, Ball);
                std::cout << "\nmouse X=" << event.motion.x << "\n mouse Y=" << event.motion.y;
                if (mball.levelcompleted == 1)
                {
                    gamerunning = nextlevelscreen(gamerunning, event);
                    mball.levelcompleted = 0;
                    level++;
                    goto chooselevel;
                }
                break;
            }
        }
    }
    SDL_DestroyTexture(Ball);
    return gamerunning;
}
