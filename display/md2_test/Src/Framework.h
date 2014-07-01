#ifndef _GLFRAMEWORK
#define _GLFRAMEWORK

//#include "glfw.h"
#include <GLFW/glfw3.h>

// Functions
void Render(GLFWwindow* window);

// A struct to hold mouse data
struct MouseInfo
{  
  int Mx,My;
  bool Mleft, Mright;
};

// Globals
extern int RunLevel;
extern bool Keys[GLFW_KEY_LAST];  // Key monitor
extern MouseInfo Mouse; // Mouse monitor

// Definitions of some windows key codes in terms of GLFW keys (Use
// uppercase characters for characer keys - 'X' is the x key for
// example.
const unsigned int
  VK_ESCAPE = GLFW_KEY_ESCAPE,
  VK_RETURN = GLFW_KEY_ENTER,
  VK_SPACE = GLFW_KEY_SPACE,
  VK_UP = GLFW_KEY_UP,
  VK_DOWN = GLFW_KEY_DOWN,
  VK_RIGHT = GLFW_KEY_RIGHT,
  VK_LEFT = GLFW_KEY_LEFT,
  VK_HOME = GLFW_KEY_HOME,
  VK_END = GLFW_KEY_END,
  VK_INSERT = GLFW_KEY_INSERT,
  VK_DELETE = GLFW_KEY_DELETE;

#endif