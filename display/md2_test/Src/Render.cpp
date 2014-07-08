
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
      buff.food = 0;
      buff.linemate = 0;
      buff.deraumere = 0;
      buff.sibur = 0;
      buff.mendiane = 0;
      buff.phiras = 0;
      buff.thystame = 0;
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
  MD2Obj player;
  MD2Obj linemate;
  MD2Obj phiras;
  MD2Obj deraumere;
  MD2Obj sibur;
  MD2Obj mendiane;
  MD2Obj thystame;

  GLuint textures[8];
  float ViewRotate=0.0f;
  long Time1,Time2,Ticks,NextFrame;
  int Frames,CurFrame=0, n;
  char Text[256];
  GLfloat Ambient[]  = { 0.9f,  0.9f,  0.9f, 10.0f};
  GLfloat Diffuse[]  = { 10.0f,  10.0f,  10.0f, 10.0f};
  GLfloat Position[] = {500.0f, 500.0f, -10.0f, 1.0f};
  glGenTextures(8,textures);
  char File[256];
  std::vector<square> objectList;

  memset(File, 0, 256);
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
  if(LoadTexture(Text,textures[0]))
    ground.SetTexture(textures[0]);
  LoadTexture("md2_test/Obj/Grass.tga" ,textures[0]);
  ground.SetTexture(textures[0]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/WalkMech.md2");
  if (ground.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  Frames = ground.GetFrameCount();
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,ground.GetTexName());
  if(LoadTexture(Text,textures[7]))
    ground.SetTexture(textures[7]);
  LoadTexture("md2_test/Obj/GenericMech.tga" ,textures[7]);
  ground.SetTexture(textures[7]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (linemate.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,linemate.GetTexName());
  if(LoadTexture(Text,textures[1]))
    linemate.SetTexture(textures[1]);
  LoadTexture("md2_test/Obj/Green.tga" ,textures[1]);
  linemate.SetTexture(textures[1]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (phiras.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,phiras.GetTexName());
  if(LoadTexture(Text,textures[2]))
    phiras.SetTexture(textures[2]);
  LoadTexture("md2_test/Obj/Red.tga" ,textures[2]);
  phiras.SetTexture(textures[2]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (deraumere.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,deraumere.GetTexName());
  if(LoadTexture(Text,textures[3]))
    deraumere.SetTexture(textures[3]);
  LoadTexture("md2_test/Obj/Blue.tga" ,textures[3]);
  deraumere.SetTexture(textures[3]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (sibur.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,sibur.GetTexName());
  if(LoadTexture(Text,textures[4]))
    sibur.SetTexture(textures[4]);
  LoadTexture("md2_test/Obj/Yellow.tga" ,textures[4]);
  sibur.SetTexture(textures[4]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (mendiane.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,mendiane.GetTexName());
  if(LoadTexture(Text,textures[5]))
    mendiane.SetTexture(textures[5]);
  LoadTexture("md2_test/Obj/Orange.tga" ,textures[5]);
  mendiane.SetTexture(textures[5]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (thystame.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,thystame.GetTexName());
  if(LoadTexture(Text,textures[6]))
    thystame.SetTexture(textures[6]);
  LoadTexture("md2_test/Obj/Pink.tga" ,textures[6]);
  thystame.SetTexture(textures[6]);

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
  objectList[0].linemate = 2;
  objectList[25].linemate = 2;
  objectList[225].linemate = 2;
  objectList[275].linemate = 2;
  objectList[35].phiras = 2;
  objectList[75].phiras = 2;
  objectList[150].phiras = 2;
  objectList[200].phiras = 2;
  objectList[356].deraumere = 2;
  objectList[380].deraumere = 2;
  objectList[36].deraumere = 2;
  objectList[205].deraumere = 2;
  objectList[368].sibur = 2;
  objectList[123].sibur = 2;
  objectList[89].sibur = 2;
  objectList[67].sibur = 2;
  objectList[182].mendiane = 2;
  objectList[160].mendiane = 2;
  objectList[395].mendiane = 2;
  objectList[320].mendiane = 2;
  objectList[267].thystame = 2;
  objectList[218].thystame = 2;
  objectList[121].thystame = 2;
  objectList[78].thystame = 2;

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
      glScalef(1.0, 1.0, 1.0);
      glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,0.0f);
      ground.Draw(CurFrame);
      glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,0.0f);
      glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
      if (objectList[n].linemate > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        linemate.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
      if (objectList[n].phiras > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        phiras.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
      if (objectList[n].deraumere > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        deraumere.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
      if (objectList[n].sibur > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        sibur.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
      if (objectList[n].mendiane > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        mendiane.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
      if (objectList[n].thystame > 0)
      {
        glTranslatef(60.5f * objectList[n].pos_x,60.5f * objectList[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        thystame.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * objectList[n].pos_x,-60.5f * objectList[n].pos_y,-30.0f);
      }      
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
  glDeleteTextures(8,textures);
}