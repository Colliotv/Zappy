
#include <vector>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <math.h>
#include <time.h>
#include "Framework.h"
#include "tga.h"
#include "MD2Loader.h"
#include "Obj.hh"
#include "Rendering.hh"
#include "Game.hh"
#include "Interface.hh"

using namespace std;

  void  drawInterface(sf::RenderWindow &window, std::vector<player> playerList);

#define FRAMEDELAY 70

Rendering::Rendering()
{
  loadObj(modelList[0], (char *)"resources/Ground.md2", (char *)"resources/Grass.tga");
  loadObj(modelList[1], (char *)"resources/Ground.md2", (char *)"resources/Grass1.tga");
  loadObj(modelList[2], (char *)"resources/Ground.md2", (char *)"resources/Green.tga");
  loadObj(modelList[3], (char *)"resources/Ground.md2", (char *)"resources/Blue.tga");
  loadObj(modelList[4], (char *)"resources/Ground.md2", (char *)"resources/Red.tga");
  loadObj(modelList[5], (char *)"resources/Ground.md2", (char *)"resources/Yellow.tga");
  loadObj(modelList[6], (char *)"resources/Ground.md2", (char *)"resources/Orange.tga");
  loadObj(modelList[7], (char *)"resources/Ground.md2", (char *)"resources/Pink.tga");
  loadObj(modelList[8], (char *)"resources/techlab.md2", (char *)"resources/techlab_diffuse.tga");
  loadObj(modelList[9], (char *)"resources/nuclear.md2", (char *)"resources/barrel02_D.tga");
  loadObj(modelList[10], (char *)"resources/WalkMech.md2", (char *)"resources/azur.tga");
  loadObj(modelList[11], (char *)"resources/WalkMech.md2", (char *)"resources/Black.tga");
  loadObj(modelList[12], (char *)"resources/WalkMech.md2", (char *)"resources/caca.tga");
  loadObj(modelList[13], (char *)"resources/WalkMech.md2", (char *)"resources/lava.tga");
  loadObj(modelList[14], (char *)"resources/WalkMech.md2", (char *)"resources/multi.tga");
  loadObj(modelList[15], (char *)"resources/WalkMech.md2", (char *)"resources/Pastis.tga");
  loadObj(modelList[16], (char *)"resources/WalkMech.md2", (char *)"resources/rouge.tga");
  loadObj(modelList[17], (char *)"resources/WalkMech.md2", (char *)"resources/vert.tga");
  loadObj(modelList[18], (char *)"resources/WalkMech.md2", (char *)"resources/violette.tga");
  loadObj(modelList[19], (char *)"resources/WalkMech.md2", (char *)"resources/White.tga");
  loadObj(modelList[20], (char *)"resources/Ground.md2", (char *)"resources/Metal.tga");
}

Rendering::~Rendering()
{
  
}

bool Rendering::LoadTexture(char *TexName, GLuint TexHandle)
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

void Rendering::loadObj(MD2Obj &object, char *pathMod, char *pathText)
{
  GLuint texture;
  char File[256];
  char Text[256];

  glGenTextures(1,&texture);
  memset(File, 0, 256);
  strcpy(File, pathMod);
  object.Load(File);
  strcpy(Text,"resources/");
  strcat(Text,object.GetTexName());
  if(LoadTexture(Text,texture))
    object.SetTexture(texture);
  LoadTexture(pathText ,texture);
  object.SetTexture(texture);
}

void  Rendering::drawObject(MD2Obj &model, float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz, int &CurFrame)
{
  glTranslatef(Tx, Ty, Tz);
  glScalef(Sx, Sy, Sz);
  glRotatef(Rx, Ry , Rz, 1.0f);
  model.Draw(CurFrame);
  glRotatef(-Rx ,-Ry ,-Rz , 1.0f);
  glScalef(1.0f/Sx, 1.0f/Sy, 1.0f/Sz);
  glTranslatef(-Tx, -Ty, -Tz);
}

void  Rendering::drawList(MD2Obj *modelList, int &CurFrame, std::vector<square> &v_square, std::vector<player> &v_player, int size_map_x, int size_map_y)
{
  unsigned int n = 0;

  while (n < v_player.size())
  {
    if (v_square[v_player[n].pos_x[0] + v_player[n].pos_y[0] * size_map_x].food != -1 && v_square[v_player[n].pos_x[0] + v_player[n].pos_y[0] * size_map_x].incant == 0 && v_player[n].cursor == 1)
      drawObject(modelList[1], 60.0f * v_player[n].pos_x[0], 60.0f * v_player[n].pos_y[0], 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_player[n].nb > 0)
      drawObject(modelList[10 + (v_player[n].nb_team % 10)], 60.0f * v_player[n].pos_x[0], 60.0f * v_player[n].pos_y[0], 10.0f, 0.5f + 0.2f * v_player[n].level, 0.5f + 0.2f * v_player[n].level, 0.5f + 0.2f * v_player[n].level, -90.0f * v_player[n].orientation -90.0f, 0.0f, 0.0f, CurFrame);
    if (v_player[n].orientation == SUD && v_player[n].pos_y[1] == size_map_y - 1)
      v_player[n].pos_y[0] = v_player[n].pos_y[1];
    if (v_player[n].orientation == NORD && v_player[n].pos_y[1] == 0)
      v_player[n].pos_y[0] = v_player[n].pos_y[1];
    if (v_player[n].orientation == OUEST && v_player[n].pos_x[1] == size_map_x - 1)
      v_player[n].pos_x[0] = v_player[n].pos_x[1];
    if (v_player[n].orientation == EST && v_player[n].pos_x[1] == 0)
      v_player[n].pos_x[0] = v_player[n].pos_x[1];
    if (v_player[n].orientation == SUD && v_player[n].pos_y[0] > v_player[n].pos_y[1])
      v_player[n].pos_y[0] -= 0.20f;
    if (v_player[n].orientation == NORD && v_player[n].pos_y[0] < v_player[n].pos_y[1])
      v_player[n].pos_y[0] += 0.20f;
    if (v_player[n].orientation == EST && v_player[n].pos_x[0] < v_player[n].pos_x[1])
      v_player[n].pos_x[0] += 0.20f;
    if (v_player[n].orientation == OUEST && v_player[n].pos_x[0] > v_player[n].pos_x[1])
      v_player[n].pos_x[0] -= 0.20f;
    usleep(300);
    n++;
  }
  n = 0;
  while (n < v_square.size())
  {
    if (v_square[n].food != -42 && v_square[n].incant == 0)
      drawObject(modelList[0], 60.0f * v_square[n].pos_x, 60.0f * v_square[n].pos_y, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, CurFrame);
    else if (v_square[n].food != -42 && v_square[n].incant == 1)
      drawObject(modelList[20], 60.0f * v_square[n].pos_x, 60.0f * v_square[n].pos_y, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, CurFrame);
    glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,15.0f);
    if (v_square[n].linemate > 0)
      drawObject(modelList[2], 25.0f, 0.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].phiras > 0)
      drawObject(modelList[3], 20.0f, -20.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].deraumere > 0)
      drawObject(modelList[4], 10.0f, -32.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].sibur > 0)
      drawObject(modelList[5], -15.0f, -17.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].mendiane > 0)
      drawObject(modelList[6], 0.0f, -10.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].thystame > 0)
      drawObject(modelList[7], -7.0f, -30.0f, 0.0f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].egg > 0)
      drawObject(modelList[8], -10.0f, 0.0f, 0.0f, 8.0f, 8.0f, 8.0f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].food > 0)
      drawObject(modelList[9], 10.0f, 0.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, 0.0f, 0.0f, CurFrame);
    glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-15.0f);
    n++;
  }
}

void  Rendering::Render(int fd, Game &parser)
{
  Interface Iface;
  sf::Vector2<int> myVect(1200, 0);
  sf::RenderWindow windowControl(sf::VideoMode(300, 800), "Camera Control Panel");
  windowControl.setPosition(myVect);
  myVect.x = 0;
  sf::RenderWindow window(sf::VideoMode(1200, 800), "Zappy", sf::Style::Default, sf::ContextSettings(32));
  window.setPosition(myVect);
  GLfloat Ambient[] = {0.9f,  0.9f,  0.9f, 10.0f};
  GLfloat Diffuse[] = {10.0f,  10.0f,  10.0f, 10.0f};
  GLfloat Position[] = {500.0f, 0.0f, -500.0f, 1.0f};

  float ViewRotate=0.0f;
  long Time1,Time2, Ticks, NextFrame;
  int Frames,CurFrame=0;

  glClearColor(0.1f,0.1f,0.1f,1.0f);

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

  glEnable(GL_FOG);
  glFogi(GL_FOG_MODE,GL_LINEAR);
  glHint(GL_FOG_HINT, GL_FASTEST);
  GLfloat fogColor[4] ={0.1f,0.1f,0.1f,1.0f};
  glFogfv(GL_FOG_COLOR,fogColor);
  glFogf(GL_FOG_START,1750.0f);
  glFogf(GL_FOG_END,3000.0f);

  Time1=Time2=clock();
  NextFrame=Time1 + FRAMEDELAY;
  Frames = modelList[10].GetFrameCount();

  while(window.isOpen())
  {
    parser.ClientRead(fd);

    glLoadIdentity();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    Time2=clock();
    Ticks=Time2-Time1;
    Time1=Time2;

    glTranslatef(-30.0f * parser.size_map_x, -100.0f,-1500.0f);
    glTranslatef(50.0f * Iface.move_X,25.0f * Iface.move_Z,-50.0f * Iface.move_Y);
    glRotatef(-70.0f,1.0f,0.0f,0.0f);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);

    drawList(modelList, CurFrame, parser.v_square, parser.v_player, parser.size_map_x, parser.size_map_y);
    Iface.drawInterface(window, windowControl, parser.v_player);

    if(Time1>NextFrame)
    {
      CurFrame++;
      NextFrame=Time1 + FRAMEDELAY;
      if(CurFrame>=Frames)
        CurFrame=0;
    }
    window.display();
    ViewRotate+=(Ticks/12000.0f);
  }
}