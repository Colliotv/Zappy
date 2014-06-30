// GLFWBase.cpp - platform independent version of the gpwiki.org
// OpenGL framework.

#include <fstream>
#include "Framework.h"

// Globals
int RunLevel = 1;
bool Keys[GLFW_KEY_LAST] = {false};  // Key monitor
MouseInfo Mouse; // Mouse monitor

// Initializationa
void InitWindow(int ScrX, int ScrY, int BPP);

// Event callback functions
void KeyCallback(int key, int action);
void MouseButtonCallback(int button, int action);
void MousePosCallback(int x, int y);

int main()
{
  int retval = 0;
  try
  {
    // Initialize the window
    InitWindow(800, 600, 32);
    // Pass control to the render function
    Render();
  }
  catch (const char* error)
  {
    // Report an error
    std::ofstream error_file("GL_ERROR.txt");
    error_file << "Caught exception:\n  " << error << '\n';
    retval = 1;
  }

  // Shut down GLFW
  glfwTerminate();
  // Return the appropriate value
  return retval;
}

// Initialize the window, can throw if something goes wrong.
void InitWindow(int ScrX, int ScrY, int BPP)
{
  // Initialize the GLFW library
  if (glfwInit() != GL_TRUE)
    throw "Failed to initialize GLFW.";

  // Create a window (8-bit depth-buffer, no alpha and stencil buffers, windowed)
  if (glfwOpenWindow(ScrX, ScrY, BPP/3, BPP/3, BPP/3, 1, 8, 1, GLFW_WINDOW) != GL_TRUE)
    throw "Failed to open window.";

  // Give the window a title
  glfwSetWindowTitle("GPWiki OpenGL Tutorial");

  // Register event callbacks
  glfwSetKeyCallback(KeyCallback);
  glfwSetMouseButtonCallback(MouseButtonCallback);
  glfwSetMousePosCallback(MousePosCallback);

  // Set the projection matrix to a normal frustum with a max depth of 500
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect_ratio = ((float)ScrX) / ScrY;
  glFrustum(.5, -.5, -.5 * aspect_ratio, .5 * aspect_ratio, 1, 500);
  glMatrixMode(GL_MODELVIEW);
}

// Wrapper for buffer swapping
void FlipBuffers()
{
  glfwSwapBuffers();
  // glfwSwapBuffers also automatically polls for input

  // If the window was closed we quit
  if (glfwGetWindowParam(GLFW_OPENED) != GL_TRUE)
    RunLevel = 0;
}

// Handle keys - updates the Keys array
void KeyCallback(int key, int action)
{
  Keys[key] = (action == GLFW_PRESS);

  if (Keys[GLFW_KEY_ESC])
    RunLevel = 0;
}

// Handle mouse button events - updates the Mouse structure
void MouseButtonCallback(int button, int action)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
    Mouse.Mleft = (action == GLFW_PRESS);
  else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    Mouse.Mright = (action == GLFW_PRESS);      
}

// Handle mouse motion - updates the Mouse structure
void MousePosCallback(int x, int y)
{
  Mouse.Mx = x;
  Mouse.My = y;
}
