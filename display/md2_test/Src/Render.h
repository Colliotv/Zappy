#define NUM_PARTICLES 5000

#include <math.h>
#include "tga.h"

typedef struct
{
  float xPos,yPos,zPos;
  float xVec,yVec,zVec;
  float r,g,b,life;
}SpriteInfo;

// Function declarations
bool LoadTexture(char *TexName, GLuint TexHandle);

// Here we go!
void Render(void)
{
  GLuint Texture[128]; // Handles to our textures
  float Rotate=0.0f;    // Rotation value to be used to spin our polygon
  float zPos=-5.0f;     // The distance to our cube
  SpriteInfo Spr[NUM_PARTICLES];
  int Index;

  // Allocate all textures in one go
  glGenTextures(128,Texture);

  // Background color
  glClearColor(0.0f,0.0f,0.0f,1.0f);

  // Setup our screen
  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,800,600);
  glLoadIdentity();
  gluPerspective(45.0f,800.0f/600.0f,0.1f,500.0f);
  glMatrixMode(GL_MODELVIEW);

  // Enable z-buffer
  glEnable(GL_DEPTH_TEST);

  // Blend
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  // Load the textures
  LoadTexture("GenericMech.tga",Texture[0]);
  LoadTexture("overlord_normal.tga",Texture[1]);
//  LoadTexture("overlord_emissive.tga",Texture[0]);
//  LoadTexture("overlord_specular.tga",Texture[1]);

  for(Index=0;Index!=NUM_PARTICLES-1;Index++)
  {
    Spr[Index].life=0.0f;
    Spr[Index].r=1.0f;
    Spr[Index].b=0.0f;
  }

  glEnable(GL_TEXTURE_2D);

  // Select particle texture
  glBindTexture(GL_TEXTURE_2D,Texture[1]);

  // This loop will run until Esc is pressed
  while(RunLevel)
  {
    if(Keys[27]) // Esc Key
      RunLevel=0;
    glLoadIdentity(); // Reset current matrix (Modelview)
    glTranslatef(0.0f,-3.0f,-12.0f);
    glRotatef((Mouse.My-300)/4.0f,1.0f,0.0f,0.0f);
    glRotatef((Mouse.Mx-400)/3.0f,0.0f,1.0f,0.0f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glDisable(GL_BLEND);

    glColor4f(0.5f,0.5f,0.5f,0.0f);

    // Select particle texture
    glBindTexture(GL_TEXTURE_2D,Texture[1]);
     
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,1.0f); glVertex3f(-2.5f,-0.1f, 2.5f);
    glTexCoord2f(1.0f,1.0f); glVertex3f( 2.5f,-0.1f, 2.5f);
    glTexCoord2f(1.0f,0.0f); glVertex3f( 2.5f,-0.1f,-2.5f);
    glTexCoord2f(0.0f,0.0f); glVertex3f(-2.5f,-0.1f,-2.5f);
    glEnd();

    glEnable(GL_BLEND);

    for(Index=0;Index!=NUM_PARTICLES-1;Index++)
    {
      if(Spr[Index].life>0.0f)
      {
        Spr[Index].xPos+=Spr[Index].xVec;
        Spr[Index].zPos+=Spr[Index].zVec;
        Spr[Index].yPos+=Spr[Index].yVec;
        Spr[Index].yVec-=0.0006f;  
        if(Spr[Index].xPos>-2.5f && Spr[Index].xPos<2.5f && Spr[Index].zPos>-2.5f && Spr[Index].zPos<2.5f)
        {
          if(Spr[Index].yPos<0.0f)
          {
            Spr[Index].yPos=0.0f;
            Spr[Index].yVec*=-0.6f;
          }
        }  
        Spr[Index].life-=0.001f;
      }
      else
      {
        Spr[Index].xPos=0.0f;
        Spr[Index].yPos=0.0f;
        Spr[Index].zPos=0.0f;
        Spr[Index].yVec=(float)((rand()%100)/2000.0f)+0.03;
        Spr[Index].xVec=(float)((rand()%100)/5000.0f)-0.01f;
        Spr[Index].zVec=(float)((rand()%100)/5000.0f)-0.01f;
        Spr[Index].life=(float)(rand()%100)/100.0f;
        Spr[Index].g=0.2f+((float)(rand()%50)/100.0f);
      }
    }

    glDepthMask(GL_FALSE);

    // Select particle texture
    glBindTexture(GL_TEXTURE_2D,Texture[0]);

    for(Index=0;Index!=NUM_PARTICLES-1;Index++)
    {
      glColor4f(Spr[Index].r,Spr[Index].g,Spr[Index].b,Spr[Index].life);

      // Draw the particle
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f); glVertex3f(Spr[Index].xPos-.1f,Spr[Index].yPos+.1f,Spr[Index].zPos);
      glTexCoord2f(0.0f,1.0f); glVertex3f(Spr[Index].xPos-.1f,Spr[Index].yPos-.1f,Spr[Index].zPos);
      glTexCoord2f(1.0f,1.0f); glVertex3f(Spr[Index].xPos+.1f,Spr[Index].yPos-.1f,Spr[Index].zPos);
      glTexCoord2f(1.0f,0.0f); glVertex3f(Spr[Index].xPos+.1f,Spr[Index].yPos+.1f,Spr[Index].zPos);
      glEnd();
    }

    glDepthMask(GL_TRUE);

    // Show our scene
    SwapBuffers(GLDC);
  }
  // Clean up textures
  glDeleteTextures(128,Texture);
 }


// Load a TGA texture
bool LoadTexture(char *TexName, GLuint TexHandle)
 {
  TGAImg Img;        // Image loader

  // Load our Texture
   if(Img.Load(TexName)!=IMG_OK)
    return false;

  glBindTexture(GL_TEXTURE_2D,TexHandle); // Set our Tex handle as current

  // Create the texture
  if(Img.GetBPP()==24)
    glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
  else if(Img.GetBPP()==32)
    glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
  else
    return false;

  // Specify filtering and edge actions
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

  return true;
 }