
#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "tga.h"
#include "MD2Loader.h"
#include "Obj.hh"
#include "Render.h"
#include "Game.hh"
#include "Interface.hh"
#include <vector>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>

using namespace std;

  void  drawInterface(sf::RenderWindow &window, std::vector<player> playerList);

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
  std::vector<square> v_player;
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
      buff.incant = 0;
      buff.egg = 0;
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

std::vector<player> refreshPlayers()
{
  std::vector<player> playerList;
  std::vector<std::string> teamList;
  player buff;
  unsigned int n = 0, m = 0;

  buff.pos_x = 0;
  buff.pos_y = 0;
  buff.nb = 1;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 22;
  buff.linemate = 2;
  buff.deraumere = 32;
  buff.sibur = 1;
  buff.mendiane = 92;
  buff.phiras = 52;
  buff.thystame = 0;
  buff.level = 1;
  buff.team = "Plop";
  playerList.push_back(buff);
  buff.pos_x = 1;
  buff.pos_y = 1;
  buff.nb = 2;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 3;
  buff.team = "Lesticocos";
  playerList.push_back(buff);
  buff.pos_x = 15;
  buff.pos_y = 10;
  buff.nb = 3;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 4;
  buff.team = "Lesticocos";
  playerList.push_back(buff);
  buff.pos_x = 10;
  buff.pos_y = 10;
  buff.nb = 4;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 2;
  buff.team = "Lesticocos";
  playerList.push_back(buff);
  buff.pos_x = 19;
  buff.pos_y = 19;
  buff.nb = 5;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 1;
  buff.team = "Plop";
  playerList.push_back(buff);
  buff.pos_x = 14;
  buff.pos_y = 6;
  buff.nb = 6;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 2;
  buff.team = "Epitech";
  playerList.push_back(buff);
  buff.pos_x = 16;
  buff.pos_y = 13;
  buff.nb = 7;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 7;
  buff.team = "Epitech";
  playerList.push_back(buff);
  buff.pos_x = 15;
  buff.pos_y = 19;
  buff.nb = 8;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 8;
  buff.team = "Plop";
  playerList.push_back(buff);
  buff.pos_x = 6;
  buff.pos_y = 3;
  buff.nb = 9;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 1;
  buff.team = "Plop";
  playerList.push_back(buff);
  buff.pos_x = 7;
  buff.pos_y = 8;
  buff.nb = 10;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 2;
  buff.team = "Lesticocos";
  playerList.push_back(buff);  
  buff.pos_y = 1;
  buff.pos_y = 2;
  buff.nb = 11;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 4;
  buff.team = "Epitech";
  playerList.push_back(buff);
  buff.pos_y = 7;
  buff.pos_y = 16;
  buff.nb = 12;
  buff.nb_team = -1;
  buff.orientation = 3;
  buff.food = 2;
  buff.linemate = 2;
  buff.deraumere = 3;
  buff.sibur = 1;
  buff.mendiane = 9;
  buff.phiras = 5;
  buff.thystame = 0;
  buff.level = 6;
  buff.team = "Epitech";
  playerList.push_back(buff);

  while (n < playerList.size())
  {
    m = 0;
    while (m < teamList.size())
    {
      if (playerList[n].team == teamList[m])
        playerList[n].nb_team = m;
      m++;
    }
    if (playerList[n].nb_team == -1)
    {
      teamList.push_back(playerList[n].team);
      playerList[n].nb_team = m;
    }
    n++;
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
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move_Y = move_Y - 0.1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move_Y = move_Y + 0.1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move_X = move_X - 0.1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move_X = move_X + 0.1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
        move_Z = move_Z - 0.1;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
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
  strcpy(Text,"resources/");
  strcat(Text,object.GetTexName());
  if(LoadTexture(Text,texture))
    object.SetTexture(texture);
  LoadTexture(pathText ,texture);
  object.SetTexture(texture);
}

void  drawObject(MD2Obj &model, float Tx, float Ty, float Tz, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz, int &CurFrame)
{
  glTranslatef(Tx, Ty, Tz);
  glScalef(Sx, Sy, Sz);
  glRotatef(Rx, Ry , Rz, 1.0f);
  model.Draw(CurFrame);
  glRotatef(-Rx ,-Ry ,-Rz , 1.0f);
  glScalef(1.0f/Sx, 1.0f/Sy, 1.0f/Sz);
  glTranslatef(-Tx, -Ty, -Tz);
}

void  Game::drawList(MD2Obj *modelList, int &CurFrame)
{
  unsigned int n = 0;

  while (n < v_player.size())
  {
    if (v_player[n].nb > 0)
      drawObject(modelList[10 + (v_player[n].nb_team % 10)], 60.0f * v_player[n].pos_x, 60.0f * v_player[n].pos_y, 10.0f, 0.5f + 0.2f * v_player[n].level, 0.5f + 0.2f * v_player[n].level, 0.5f + 0.2f * v_player[n].level, -90.0f * v_player[n].orientation -90.0f, 0.0f, 0.0f, CurFrame);
    n++;
  }    
  n = 0;
  while (n < v_square.size())
  {
    if (v_square[n].food != -1 && v_square[n].incant == 0)
      drawObject(modelList[0], 60.0f * v_square[n].pos_x, 60.0f * v_square[n].pos_y, 0.0f, 1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, CurFrame);
    if (v_square[n].food != -1 && v_square[n].incant == 1)
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

void  Game::Rendering(sf::RenderWindow & /*window*/, int fd)
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
  std::vector<player> v_playerForInterface;
  MD2Obj  modelList[22];
  float ViewRotate=0.0f;
  long Time1,Time2, Ticks, NextFrame;
  int Frames,CurFrame=0;

  loadObj(modelList[0], (char *)"resources/Ground.md2", (char *)"resources/Grass.tga");
  // loadObj(modelList[1], (char *)"resources/exclamation.md2", (char *)"resources/Yellow.tga");
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
  // loadObj(modelList[21], (char *)"resources/LevelUp.md2", (char *)"resources/Yellow.tga");  
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
  Frames = modelList[10].GetFrameCount();

  v_square = createList(20.0, 20.0);
  v_player = refreshPlayers();
  v_square[100].linemate = 2;
  v_square[25].linemate = 2;
  v_square[225].linemate = 2;
  v_square[275].linemate = 2;
  v_square[100].phiras = 2;
  v_square[75].phiras = 2;
  v_square[150].phiras = 2;
  v_square[200].phiras = 2;
  v_square[100].deraumere = 2;
  v_square[380].deraumere = 2;
  v_square[36].deraumere = 2;
  v_square[205].deraumere = 2;
  v_square[100].sibur = 2;
  v_square[123].sibur = 2;
  v_square[89].sibur = 2;
  v_square[67].sibur = 2;
  v_square[67].incant = 1;
  v_square[100].mendiane = 2;
  v_square[160].mendiane = 2;
  v_square[395].mendiane = 2;
  v_square[320].mendiane = 2;
  v_square[320].incant = 1;
  v_square[100].thystame = 2;
  v_square[218].thystame = 2;
  v_square[121].thystame = 2;
  v_square[78].thystame = 2;
  v_square[100].egg = 2;
  v_square[100].food = 2;

  while(window.isOpen())
  {
    // this->ClientRead(fd);

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

    // drawObject(modelList[21], 50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, CurFrame);

    this->drawList(modelList, CurFrame);
    v_playerForInterface = this->v_player;
    Iface.drawInterface(windowControl, v_playerForInterface);

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