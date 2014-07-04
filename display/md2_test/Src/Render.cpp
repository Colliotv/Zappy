
#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "tga.h"
#include "MD2Loader.h"
#include "Obj.hh"
#include "Render.h"
#include <vector>
#include <unistd.h>

using namespace std;

#define FRAMEDELAY 70

  float move_X = 1.0;
  float move_Y = 1.0;
  float move_Z = 1.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
  else if (key == GLFW_KEY_RIGHT)
    move_X = move_X - 0.1;
  else if (key == GLFW_KEY_LEFT)
    move_X = move_X + 0.1;
  else if (key == GLFW_KEY_UP)
    move_Y = move_Y - 0.1;
  else if (key == GLFW_KEY_DOWN)
    move_Y = move_Y + 0.1;
  else if (key == GLFW_KEY_KP_ADD)
    move_Z = move_Z - 0.1;
  else if (key == GLFW_KEY_KP_SUBTRACT)
    move_Z = move_Z + 0.1;
}

bool LoadTexture(char *TexName, GLuint TexHandle)
{
  TGAImg Img;

  if(Img.Load(TexName)!=IMG_OK)
    return false;
  glBindTexture(GL_TEXTURE_2D,TexHandle);
  if(Img.GetBPP()==24)
    glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
  else if(Img.GetBPP()==32)
    glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
  else
    return false;
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
  return true;
}

std::vector<square> createList(float size_x, float size_y)
{
  std::vector<square> objectList;
  square buff;
  float x = 0.0f;
  float y = 0.0f;

  while (x < size_x)
  {
    y = 0.0f;
    while (y < size_y)
    {
      buff.pos_x = x;
      buff.pos_y = y;
      buff.linemate = 2;
      objectList.push_back(buff);
      y++;
    }
    x++;
  }
  return (objectList);
}

void  Rendering(GLFWwindow* window)
{
  MD2Obj ground;
  GLuint texGround;
  float ViewRotate=0.0f;
  long Time1,Time2,Ticks,NextFrame;
  int Frames,CurFrame=0, n;
  char Text[256];
  GLfloat Ambient[]  = { 0.9f,  0.9f,  0.9f, 10.0f};
  GLfloat Diffuse[]  = { 10.0f,  10.0f,  10.0f, 10.0f};
  GLfloat Position[] = {500.0f, 500.0f, -10.0f, 1.0f};
  glGenTextures(1,&texGround);
  char File[256];
  std::vector<square> objectList;

  strcpy(File, "md2_test/Obj/Ground.md2");
  if (ground.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  Frames = ground.GetFrameCount();
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,ground.GetTexName());
  if(LoadTexture(Text,texGround))
    ground.SetTexture(texGround);
  LoadTexture("md2_test/Obj/Grass.tga" ,texGround);
  ground.SetTexture(texGround);
  glClearColor(0.2f,0.2f,0.2f,1.0f);

  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,1200,800);
  glLoadIdentity();
  glFrustum(-.5f,.5f,-.5f*(800.0f/1200.0f),.5f*(800.0f/1200.0f),1.0f,3000.0f);
  glMatrixMode(GL_MODELVIEW);
  
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
  Time1=Time2=clock();
  NextFrame=Time1 + FRAMEDELAY;

  objectList = createList(20.0, 20.0);

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    Time2=clock();
    Ticks=Time2-Time1;
    Time1=Time2;

    glTranslatef(-600.0f, -100.0f,-1000.0f);
    glTranslatef(50.0f * move_X,25.0f * move_Z,-50.0f * move_Y);
    glRotatef(-60.0f,1.0f,0.0f,0.0f);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
    // glRotatef(ViewRotate,0.0f,0.0f,1.0f);

    n = 0;
    while (n < objectList.size())
    {
      // glScalef(1.1, 1.1, 1.1);
      glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,0.0f);
      ground.Draw(CurFrame);
      glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,0.0f);
      // glScalef(-1.1, -1.1, -1.1);
      n++;
    }
    if(Time1>NextFrame)
    {
      CurFrame++;
      NextFrame=Time1 + FRAMEDELAY;
      if(CurFrame>=Frames)
        CurFrame=0;
    }
    glfwSwapBuffers(window);
    ViewRotate+=(Ticks/12000.0f);
  }
  glDeleteTextures(1,&texGround);
}