
#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <unistd.h>
#include "Game.hh"
#include "tga.h"
#include "MD2Loader.h"
#include "Obj.hh"
#include "Render.h"

using namespace std;

#define FRAMEDELAY 70

  float move_X = 1.0;
  float move_Y = 1.0;
  float move_Z = 1.0;

void key_callback(GLFWwindow* window, int key, int, int action, int)
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
  std::vector<square> v_square;
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
      v_square.push_back(buff);
      y++;
    }
    x++;
  }
  return (v_square);
}

std::vector<player> refreshPlayers(float size_x, float size_y)
{
  std::vector<player> v_player;
  player buff;
  float x = 0.0f;
  float y = 0.0f;

  while (x < size_x)
  {
    y = 0.0f;
    while (y < size_y)
    {
      buff.pos_x = x;
      buff.pos_y = y;
      buff.nb = -1;
      buff.team = -1;
      buff.food = 0;
      buff.linemate = 0;
      buff.deraumere = 0;
      buff.sibur = 0;
      buff.mendiane = 0;
      buff.phiras = 0;
      buff.thystame = 0;
      v_player.push_back(buff);
      y++;
    }
    x++;
  }
  return (v_player);
}

void  Game::Rendering(GLFWwindow* window, int fd)
{
  MD2Obj groundObj;
  MD2Obj playerObj;
  MD2Obj linemateObj;
  MD2Obj phirasObj;
  MD2Obj deraumereObj;
  MD2Obj siburObj;
  MD2Obj mendianeObj;
  MD2Obj thystameObj;

  GLuint textures[8];
  float ViewRotate=0.0f;
  long Time1,Time2,Ticks,NextFrame;
  int Frames,CurFrame=0;
  unsigned int n;
  char Text[256];
  GLfloat Ambient[]  = { 0.9f,  0.9f,  0.9f, 10.0f};
  GLfloat Diffuse[]  = { 10.0f,  10.0f,  10.0f, 10.0f};
  GLfloat Position[] = {500.0f, 500.0f, -10.0f, 1.0f};
  glGenTextures(8,textures);
  char File[256];
//  std::vector<square> v_square;
//  std::vector<player> v_player;
  

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (groundObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  Frames = groundObj.GetFrameCount();
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,groundObj.GetTexName());
  if(LoadTexture(Text,textures[0]))
    groundObj.SetTexture(textures[0]);
  LoadTexture((char *)"md2_test/Obj/Grass.tga" ,textures[0]);
  groundObj.SetTexture(textures[0]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/WalkMech.md2");
  if (playerObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  Frames = playerObj.GetFrameCount();
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,playerObj.GetTexName());
  if(LoadTexture(Text,textures[7]))
    playerObj.SetTexture(textures[7]);
  LoadTexture((char *)"md2_test/Obj/GenericMech.tga" ,textures[7]);
  playerObj.SetTexture(textures[7]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (linemateObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,linemateObj.GetTexName());
  if(LoadTexture(Text,textures[1]))
    linemateObj.SetTexture(textures[1]);
  LoadTexture((char *)"md2_test/Obj/Green.tga" ,textures[1]);
  linemateObj.SetTexture(textures[1]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (phirasObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,phirasObj.GetTexName());
  if(LoadTexture(Text,textures[2]))
    phirasObj.SetTexture(textures[2]);
  LoadTexture((char *)"md2_test/Obj/Red.tga" ,textures[2]);
  phirasObj.SetTexture(textures[2]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (deraumereObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,deraumereObj.GetTexName());
  if(LoadTexture(Text,textures[3]))
    deraumereObj.SetTexture(textures[3]);
  LoadTexture((char *)"md2_test/Obj/Blue.tga" ,textures[3]);
  deraumereObj.SetTexture(textures[3]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (siburObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,siburObj.GetTexName());
  if(LoadTexture(Text,textures[4]))
    siburObj.SetTexture(textures[4]);
  LoadTexture((char *)"md2_test/Obj/Yellow.tga" ,textures[4]);
  siburObj.SetTexture(textures[4]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (mendianeObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,mendianeObj.GetTexName());
  if(LoadTexture(Text,textures[5]))
    mendianeObj.SetTexture(textures[5]);
  LoadTexture((char *)"md2_test/Obj/Orange.tga" ,textures[5]);
  mendianeObj.SetTexture(textures[5]);

  memset(File, 0, 256);
  strcpy(File, "md2_test/Obj/Ground.md2");
  if (thystameObj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,thystameObj.GetTexName());
  if(LoadTexture(Text,textures[6]))
    thystameObj.SetTexture(textures[6]);
  LoadTexture((char *)"md2_test/Obj/Pink.tga" ,textures[6]);
  thystameObj.SetTexture(textures[6]);

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

  // v_square = createList(20.0, 20.0);
  // v_player = refreshPlayers(20.0, 20.0);
  // v_square[0].linemate = 2;
  // v_square[25].linemate = 2;
  // v_square[225].linemate = 2;
  // v_square[275].linemate = 2;
  // v_square[35].phiras = 2;
  // v_square[75].phiras = 2;
  // v_square[150].phiras = 2;
  // v_square[200].phiras = 2;
  // v_square[356].deraumere = 2;
  // v_square[380].deraumere = 2;
  // v_square[36].deraumere = 2;
  // v_square[205].deraumere = 2;
  // v_square[368].sibur = 2;
  // v_square[123].sibur = 2;
  // v_square[89].sibur = 2;
  // v_square[67].sibur = 2;
  // v_square[182].mendiane = 2;
  // v_square[160].mendiane = 2;
  // v_square[395].mendiane = 2;
  // v_square[320].mendiane = 2;
  // v_square[267].thystame = 2;
  // v_square[218].thystame = 2;
  // v_square[121].thystame = 2;
  // v_square[78].thystame = 2;

  while(!glfwWindowShouldClose(window))
  {
    this->ClientRead(fd);

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
    while (n < v_square.size())
    {
      glScalef(1.0, 1.0, 1.0);
      glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,0.0f);
      groundObj.Draw(CurFrame);
      glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,0.0f);
      glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
      if (v_square[n].linemate > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        linemateObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
      }      
      if (v_square[n].phiras > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        phirasObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
      }      
      if (v_square[n].deraumere > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        deraumereObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
      }      
      if (v_square[n].sibur > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        siburObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
      }      
      if (v_square[n].mendiane > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        mendianeObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
      }      
      if (v_square[n].thystame > 0)
      {
        glTranslatef(60.5f * v_square[n].pos_x,60.5f * v_square[n].pos_y,30.0f);
        glScalef(0.1, 0.1, 0.1);
        thystameObj.Draw(CurFrame);
        glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
        glTranslatef(-60.5f * v_square[n].pos_x,-60.5f * v_square[n].pos_y,-30.0f);
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