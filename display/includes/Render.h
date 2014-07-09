
#ifndef _RENDER_H_
#define _RENDER_H_

#define NUM_PARTICLES 5000

#include <math.h>
#include <vector>
#include "tga.h"
#include "Framework.h"
#include "Obj.hh"
#include "MD2Loader.h"

typedef struct
{
  float xPos,yPos,zPos;
  float xVec,yVec,zVec;
  float r,g,b,life;
}SpriteInfo;

void  Rendering(GLFWwindow* window, int);

#endif