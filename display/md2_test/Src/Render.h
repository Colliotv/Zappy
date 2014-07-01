#define NUM_PARTICLES 5000

#include <math.h>
#include "tga.h"

typedef struct
{
  float xPos,yPos,zPos;
  float xVec,yVec,zVec;
  float r,g,b,life;
}SpriteInfo;