#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "imp/currentframe.hpp"
#include "imp/background.hpp"
float initX, initY;
void right();
void left();
void up(float);
void down(float);
void uprt(float);
void uplt(float);
void downrt(float);
void downlt(float);

frame tframe;
class ballAI
{
public:
  bool levelcompleted = 0;
  void move(float, float, float, float, SDL_Renderer *render, SDL_Texture *texture);
  void getX(float);
  void getY(float);
  float giveX();
  float giveY();
  void destination(float, float);

private:
  int i;
  float slope;
  float goalX, goalY;
};

// getting ball initial position
void ballAI::getX(float x)
{
  initX = x;
}
void ballAI::getY(float y)
{
  initY = y;
}

// getting goal position

void ballAI::destination(float x, float y)
{
  goalX = x;
  goalY = y;
}

// sending position of the ball
float ballAI::giveX()
{
  return initX;
}
float ballAI::giveY()
{
  return initY;
}

// moving the ball

void ballAI::move(float initballX, float initballY, float initmouseX, float initmouseY, SDL_Renderer *render, SDL_Texture *texture)
{

  // distance between ball and mouse

  float a, b, d, x1, y1, x2, y2;
  float speed;
  int i, direction = 0;
  d = sqrt(((initmouseX - initballX) * (initmouseX - initballX)) + ((initmouseY - initballY) * (initmouseY - initballY)));
  std::cout << " \n distance= " << d;
  // calculating slope
  slope = (initballY - initmouseY) / (initballX - initmouseX);

  if (initballX > initmouseX && initballY > initmouseY) // uplt->downrt
    direction = 4;
  else if (initballX < initmouseX && initballY > initmouseY) // uprt->downlt
    direction = 5;
  else if (initballX < initmouseX && initballY < initmouseY) // downrt->uplt
    direction = 6;
  else if (initballX > initmouseX && initballY < initmouseY) // downlt->uprt
    direction = 7;
  else if (initballX == initmouseX && initballY > initmouseY) // up->down
    direction = 0;
  if (initballX == initmouseX && initballY < initmouseY) // down->up
    direction = 1;
  else if (initballX > initmouseX && initballY == initmouseY) // left->right
    direction = 2;
  else if (initballX > initmouseX && initballY == initmouseY) // right->left
    direction = 3;
  std::cout << "\n direction =" << direction;
  std::cout << "distance==" << d;

  for (i = d; i > 0; i--)
  {
    // goal code
    if ((initX >= goalX && initX - 25 <= goalX + 25) && (initY >= goalY - 25 && initY <= goalY + 25))
    {
      initX = goalX;
      initY = goalY;
      levelcompleted = 1;
      break;
      std::cout << "\n ball has been caught \n";
    }
    // movement code
    if (initY <= 0.00)
    {
      if (direction == 7)
      {
        direction = 4;
        slope = (-1) * slope;
      }
      else if (direction == 6)
      {
        slope = (-1) * slope;
        direction = 5;
      }
      else if (direction == 1)
      {
        slope = (-1) * slope;
        direction = 0;
      }

      std::cout << "\n new dirextion =" << direction;
    }
    else if (initY >= 500.00)
    {
      if (direction == 4)
      {
        direction = 7;
        slope = (-1) * slope;
      }
      else if (direction == 5)
      {
        slope = (-1) * slope;
        direction = 6;
      }
      else if (direction == 0)
      {
        slope = (-1) * slope;
        direction = 1;
      }

      std::cout << "\n new dirextion =" << direction;
    }
    else if (initX <= 0.00)
    {
      if (direction == 6)
      {
        direction = 7;
        slope = (-1) * slope;
      }
      else if (direction == 5)
      {
        slope = (-1) * slope;
        direction = 4;
      }
      else if (direction == 3)
      {
        slope = (-1) * slope;
        direction = 2;
      }

      std::cout << "\n new dirextion =" << direction;
    }
    else if (initX >= 480.00)
    {
      if (direction == 7)
      {
        direction = 6;
        slope = (-1) * slope;
      }
      else if (direction == 4)
      {
        slope = (-1) * slope;
        direction = 5;
      }
      else if (direction == 2)
      {
        slope = (-1) * slope;
        direction = 3;
      }

      std::cout << "\n new dirextion =" << direction;
    }
    // choosing path to move
    switch (direction)
    {
    case 0:
      down(slope);
      break;
    case 1:
      up(slope);
      break;
    case 2:
      right();
      break;
    case 3:
      left();
      break;
    case 4:
      downrt(slope);
      break;
    case 5:
      downlt(slope);
      break;
    case 6:
      uplt(slope);
      break;
    case 7:
      uprt(slope);
      break;
    }

    std::cout << "\n x= " << initX << "\n y= " << initY;
    tframe.copy(texture, 16, 16, initX, initY);
    tframe.present();
  }
}
void uprt(float slope)
{
  initX = 1 + initX;
  initY = initY + slope;
}
void uplt(float slope)
{
  initX = initX - 1;
  initY = initY - slope;
}
void downrt(float slope)
{
  initX = initX + 1;
  initY = initY + slope;
}
void downlt(float slope)
{
  initX = initX - 1;
  initY = initY - slope;
}
void right()
{
  initX = initX + 1;
}
void left()
{
  initX = initX - 1;
}
void up(float slope)
{
  initY = initY + 0.00000001;
}
void down(float slope)
{
  initY = initY + 0.00000001;
}
/*
down=0
up=1
right=2
left=3
downrt=4
downlt=5
uplt=6
uprt=7
*/