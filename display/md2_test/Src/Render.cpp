
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
  #include    <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

#define FRAMEDELAY 70

 int RunLevel = 1;
 float move_X = 1.0;
 float move_Y = 1.0;
 float move_Z = 1.0;

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

std::vector<player> refreshPlayers(float size_x, float size_y)
{
  std::vector<player> playerList;
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
      playerList.push_back(buff);
      y++;
    }
    x++;
  }
  return (playerList);
}

void  eventsManager(sf::Window &window)
{
  sf::Event event;

  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      window.close();
    if (event.type == sf::Event::KeyPressed)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move_Y = move_Y - 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move_Y = move_Y + 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move_X = move_X - 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move_X = move_X + 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        move_Z = move_Z - 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
        move_Z = move_Z + 0.1;
    }
  }
}

void loadObj(MD2Obj &object, char *pathMod, char *pathText)
{
  GLuint texture;
  char File[256];
  char Text[256];

  glGenTextures(1,&texture);
  memset(File, 0, 256);
  strcpy(File, pathMod);
  object.Load(File);
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,object.GetTexName());
  if(LoadTexture(Text,texture))
    object.SetTexture(texture);
  LoadTexture(pathText ,texture);
  object.SetTexture(texture);
}

void  drawObjects(std::vector<square> objectList, std::vector<player> playerList, MD2Obj *modelList, int &CurFrame)
{
  unsigned int n = 0;

  while (n < objectList.size())
  {
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,0.0f);
    modelList[0].Draw(CurFrame);
    glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,0.0f);
    glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
    if (playerList[n].nb > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
        // glScalef(1.0, 1.0, 1.0);
      modelList[1].Draw(CurFrame);
        // glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    if (objectList[n].linemate > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glTranslatef(20.0f, 5.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[2].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-20.0f, -5.0f, -0.0f);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    if (objectList[n].phiras > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[3].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }
    if (objectList[n].deraumere > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glTranslatef(10.0f, -10.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[4].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-10.0f, 10.0f, -0.0f);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    if (objectList[n].sibur > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glTranslatef(-20.0f, -20.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[5].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(20.0f, 20.0f, -0.0f);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    if (objectList[n].mendiane > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glTranslatef(0.0f, -25.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[6].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(0.0f, 25.0f, 0.0f);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    if (objectList[n].thystame > 0)
    {
      glTranslatef(60.0f * objectList[n].pos_x,60.0f * objectList[n].pos_y,30.0f);
      glTranslatef(-15.0f, -5.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[7].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(15.0f, 5.0f, 0.0f);
      glTranslatef(-60.0f * objectList[n].pos_x,-60.0f * objectList[n].pos_y,-30.0f);
    }      
    n++;
  }
}

void  Rendering(sf::RenderWindow &/*window*/)
{
  sf::Window window(sf::VideoMode(1200, 800), "Zappy", sf::Style::Default, sf::ContextSettings(32));
  GLfloat Ambient[]  = {0.9f,  0.9f,  0.9f, 10.0f};
  GLfloat Diffuse[]  = {10.0f,  10.0f,  10.0f, 10.0f};
  GLfloat Position[] = {500.0f, 0.0f, -500.0f, 1.0f};
  std::vector<square> objectList;
  std::vector<player> playerList;
  MD2Obj  modelList[8];
  float ViewRotate=0.0f;
  long Time1,Time2, Ticks, NextFrame;
  int Frames,CurFrame=0;

  loadObj(modelList[0], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/caisse.tga");
  loadObj(modelList[1], (char *)"md2_test/Obj/WalkMech.md2", (char *)"md2_test/Obj/RedMech.tga");
  loadObj(modelList[2], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Green.tga");
  loadObj(modelList[3], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Blue.tga");
  loadObj(modelList[4], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Red.tga");
  loadObj(modelList[5], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Yellow.tga");
  loadObj(modelList[6], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Orange.tga");
  loadObj(modelList[7], (char *)"md2_test/Obj/Ground.md2", (char *)"md2_test/Obj/Pink.tga");

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
  Frames = modelList[1].GetFrameCount();

  objectList = createList(20.0, 20.0);
  playerList = refreshPlayers(20.0, 20.0);
  objectList[100].linemate = 2;
  objectList[25].linemate = 2;
  objectList[225].linemate = 2;
  objectList[275].linemate = 2;
  objectList[100].phiras = 2;
  objectList[75].phiras = 2;
  objectList[150].phiras = 2;
  objectList[200].phiras = 2;
  objectList[100].deraumere = 2;
  objectList[380].deraumere = 2;
  objectList[36].deraumere = 2;
  objectList[205].deraumere = 2;
  objectList[100].sibur = 2;
  objectList[123].sibur = 2;
  objectList[89].sibur = 2;
  objectList[67].sibur = 2;
  objectList[100].mendiane = 2;
  objectList[160].mendiane = 2;
  objectList[395].mendiane = 2;
  objectList[320].mendiane = 2;
  objectList[100].thystame = 2;
  objectList[218].thystame = 2;
  objectList[121].thystame = 2;
  objectList[78].thystame = 2;
  playerList[101].nb = 1;
  playerList[190].nb = 2;
  playerList[300].nb = 3;

  while(window.isOpen())
  {
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

    eventsManager(window);
    drawObjects(objectList, playerList, modelList, CurFrame);

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