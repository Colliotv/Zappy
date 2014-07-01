
#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "tga.h"
#include "MD2Loader.h"

using namespace std;

#define FRAMEDELAY 70

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

void Render(GLFWwindow* window)
{
  MD2Obj Obj;
  GLuint Texture[32];  
  float ViewRotate=0.0f;
  long Time1,Time2,Ticks,NextFrame;
  int Frames,CurFrame=0;
  char Text[256];
  GLfloat Ambient[]  = { 0.1f,  0.1f,  0.1f, 1.0f};
  GLfloat Diffuse[]  = { 1.0f,  1.0f,  1.0f, 1.0f};
  GLfloat Position[] = {10.0f, 60.0f, 10.0f, 1.0f};

  glGenTextures(32,Texture);
	 char File[256];
  strcpy(File, "md2_test/Obj/WalkMech.md2");
  if (Obj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }
  Frames = Obj.GetFrameCount();
  strcpy(Text,"md2_test/Obj/");
  strcat(Text,Obj.GetTexName());
  if(LoadTexture(Text,Texture[0]))
    Obj.SetTexture(Texture[0]);		
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,800,600);
  glLoadIdentity();
  glFrustum(-.5f,.5f,-.5f*(600.0f/800.0f),.5f*(600.0f/800.0f),1.0f,500.0f);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
  Time1=Time2=clock();
  NextFrame=Time1 + FRAMEDELAY;
  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(window, GL_TRUE);
    glLoadIdentity(); 
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    Time2=clock();
    Ticks=Time2-Time1;
    Time1=Time2;
    glTranslatef(0.0f,-10.0f,-90.0f);
    glRotatef(-60.0f,1.0f,0.0f,0.0f);
	  glLightfv(GL_LIGHT0,GL_POSITION,Position);
    glRotatef(ViewRotate,0.0f,0.0f,1.0f);
    Obj.Draw(CurFrame);
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
  glDeleteTextures(32,Texture);
}


