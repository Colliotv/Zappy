#include "Framework.h"
#include <iostream>
#include <math.h>
#include <time.h>
#include "tga.h"
#include "MD2Loader.h"

using namespace std;

#define FRAMEDELAY 70

// Function declarations
bool LoadTexture(char *TexName, GLuint TexHandle);

// Here we go!
void Render(void)
{
  MD2Obj Obj; // Our object class
  GLuint Texture[32]; // Texture store       //32 avant

  float ViewRotate=0.0f; // A few vars to handle view rotation, animation and time base values
  long Time1,Time2,Ticks,NextFrame;
  int Frames,CurFrame=0;

  char Text[256]; // General purpose string

  GLfloat Ambient[]  = { 0.1f,  0.1f,  0.1f, 1.0f};	 // Ambient light value
  GLfloat Diffuse[]  = { 1.0f,  1.0f,  1.0f, 1.0f};	 // Diffuse light value
  GLfloat Position[] = {10.0f, 60.0f, 10.0f, 1.0f};	 // Light position

  // Allocate all textures in one go
  glGenTextures(32,Texture);

	 char File[256]; // General purpose string	// Load our Object
   strcpy(File, "../Obj/WalkMech.md2");
  if (Obj.Load(File))
  {
    RunLevel = 0;
    cout << "Unable to load Object!\n";
    return;
  }


		// Find out how many frames we have
  Frames = Obj.GetFrameCount();


		// Load a texture for our object
  strcpy(Text,"../Obj/");
  strcat(Text,Obj.GetTexName());
		
  if(LoadTexture(Text,Texture[0]))
    Obj.SetTexture(Texture[0]);		

  // Background color
  glClearColor(0.0f,0.0f,0.0f,1.0f);


  // Setup our screen
  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,800,600);
  glLoadIdentity();
  glFrustum(-.5f,.5f,-.5f*(600.0f/800.0f),.5f*(600.0f/800.0f),1.0f,500.0f);
  glMatrixMode(GL_MODELVIEW);


  // Enable z-buffer
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);


		// Enable Lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);	// Set the ambient lighting value for Light0
  glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);	// Set the diffuse lighting value for Light0


		// Set up TBM
  Time1=Time2=clock();
  NextFrame=Time1 + FRAMEDELAY;

  
  // Main Loop
   while(RunLevel)
    {
				  // Esc quits
      if(Keys[VK_ESCAPE])
       RunLevel=0;


     // Reset view
     glLoadIdentity(); 
     glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


     // Get ticks since last frame
     Time2=clock();
     Ticks=Time2-Time1;
     Time1=Time2;


    // Set up the view 
    glTranslatef(0.0f,-10.0f,-90.0f); // dernier param = longueur
    glRotatef(-60.0f,1.0f,0.0f,0.0f);

    // Set Light Position
	  glLightfv(GL_LIGHT0,GL_POSITION,Position);		// Set position for the light

     // Rotate view
    glRotatef(ViewRotate,0.0f,0.0f,1.0f);


					// Draw our Object
    Obj.Draw(CurFrame);

		// Advance the frame counter
    if(Time1>NextFrame)
    {
      CurFrame++;
      NextFrame=Time1 + FRAMEDELAY;

      if(CurFrame>=Frames)
        CurFrame=0;
    }

     // Show our scene
     FlipBuffers();


     // Rotate view for next frame
     ViewRotate+=(Ticks/12000.0f);
    }


  // Clean up textures
  glDeleteTextures(32,Texture);
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
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

  return true;
 }