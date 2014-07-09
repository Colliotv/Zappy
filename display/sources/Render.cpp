
#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "tga.h"
#include "MD2Loader.h"
#include "Obj.hh"
#include "Render.h"
#include "Game.hh"
#include <vector>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector2.hpp>

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
      buff.level = -1;
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

void  Game::drawObjects(MD2Obj *modelList, int &CurFrame)
{
  unsigned int n = 0;

//  std::cout << "---> " << v_square.size();
  while (n < v_square.size())
  {
    glScalef(1.0, 1.0, 1.0);
    glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,0.0f);
    modelList[0].Draw(CurFrame);
    glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,0.0f);
    glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
    if (v_player.size() > 0 && v_player[n].nb > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
        // glScalef(1.0, 1.0, 1.0);
      modelList[1].Draw(CurFrame);
        // glScalef(1.0/1.0, 1.0/1.0, 1.0/1.0);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    if (v_square[n].linemate > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glTranslatef(20.0f, 5.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[2].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-20.0f, -5.0f, -0.0f);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    if (v_square[n].phiras > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[3].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }
    if (v_square[n].deraumere > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glTranslatef(10.0f, -10.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[4].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(-10.0f, 10.0f, -0.0f);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    if (v_square[n].sibur > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glTranslatef(-20.0f, -20.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[5].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(20.0f, 20.0f, -0.0f);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    if (v_square[n].mendiane > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glTranslatef(0.0f, -25.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[6].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(0.0f, 25.0f, 0.0f);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    if (v_square[n].thystame > 0)
    {
      glTranslatef(60.0f * v_square[n].pos_x,60.0f * v_square[n].pos_y,30.0f);
      glTranslatef(-15.0f, -5.0f, 0.0f);
      glScalef(0.1, 0.1, 0.1);
      modelList[7].Draw(CurFrame);
      glScalef(1.0/0.1, 1.0/0.1, 1.0/0.1);
      glTranslatef(15.0f, 5.0f, 0.0f);
      glTranslatef(-60.0f * v_square[n].pos_x,-60.0f * v_square[n].pos_y,-30.0f);
    }      
    n++;
  }
}

bool sortByTeam(const player &lhs, const player &rhs) {return lhs.team < rhs.team;}
bool sortByLevel(const player &lhs, const player &rhs) {return lhs.level < rhs.level;}

void eventsInterface(sf::RenderWindow &window)
{
  sf::Event event;

  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::KeyPressed)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        move_Y = move_Y - 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        move_Y = move_Y + 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        move_X = move_X - 0.1;
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        move_X = move_X + 0.1;
    }
  }
}

void  drawInterface(sf::RenderWindow &window, std::vector<player> v_player)
{
  std::sort(v_player.begin(), v_player.end(), sortByLevel);
  std::sort(v_player.begin(), v_player.end(), sortByTeam);
  sf::RectangleShape rect;
  sf::Font font;
  sf::Text text;
  std::string str;

  window.clear();
  if (!font.loadFromFile("resources/LCD.otf"))
    std::cout << "Error : failed to load font" << std::endl;
  rect.setSize(sf::Vector2f(280, 80));
  rect.setFillColor(sf::Color(200, 200, 200, 128));
  rect.setOutlineThickness(10);
  rect.setOutlineColor(sf::Color(120, 120, 120, 128));
  rect.setPosition(10, 10);
  window.draw(rect);
  rect.setPosition(10, 110);
  window.draw(rect);
  rect.setPosition(10, 210);
  window.draw(rect);
  rect.setPosition(10, 310);
  window.draw(rect);
  rect.setPosition(10, 410);
  window.draw(rect);
  rect.setPosition(10, 510);
  window.draw(rect);
  rect.setPosition(10, 610);
  window.draw(rect);
  rect.setPosition(10, 710);
  window.draw(rect);
  rect.setPosition(10, 810);

  text.setFont(font);
  text.setColor(sf::Color::Red);
  text.setString("Team Zappy");
  text.setCharacterSize(24);
  text.setPosition(20, 20);
  window.draw(text);
  text.setColor(sf::Color::Green);
  text.setString("Player 1");
  text.setPosition(20, 120);
  window.draw(text);
  text.setString("Player 2");
  text.setPosition(20, 220);
  window.draw(text);
  text.setString("Player 3");
  text.setPosition(20, 320);
  window.draw(text);
  text.setString("Player 4");
  text.setPosition(20, 420);
  window.draw(text);
  text.setString("Player 5");
  text.setPosition(20, 520);
  window.draw(text);
  text.setString("Player 6");
  text.setPosition(20, 620);
  window.draw(text);
  text.setString("Player 7");
  text.setPosition(20, 720);
  window.draw(text);

  window.display();

  eventsInterface(window);
}

void  Game::Rendering(sf::RenderWindow &/*window*/, int fd)
{
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
  MD2Obj  modelList[8];
  float ViewRotate=0.0f;
  long Time1,Time2, Ticks, NextFrame;
  int Frames,CurFrame=0;

  loadObj(modelList[0], (char *)"resources/Ground.md2", (char *)"resources/Grass.tga");
  loadObj(modelList[1], (char *)"resources/WalkMech.md2", (char *)"resources/RedMech.tga");
  loadObj(modelList[2], (char *)"resources/Ground.md2", (char *)"resources/Green.tga");
  loadObj(modelList[3], (char *)"resources/Ground.md2", (char *)"resources/Blue.tga");
  loadObj(modelList[4], (char *)"resources/Ground.md2", (char *)"resources/Red.tga");
  loadObj(modelList[5], (char *)"resources/Ground.md2", (char *)"resources/Yellow.tga");
  loadObj(modelList[6], (char *)"resources/Ground.md2", (char *)"resources/Orange.tga");
  loadObj(modelList[7], (char *)"resources/Ground.md2", (char *)"resources/Pink.tga");

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

  while(window.isOpen())
  {
    this->ClientRead(fd);

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
    this->drawObjects(modelList, CurFrame);
    v_playerForInterface = this->v_player;
    drawInterface(windowControl, v_playerForInterface);


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