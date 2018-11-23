#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "types.h"

namespace oak
{
  class Window
  {
    static GLFWwindow* window;
    
    static uint screenW;
    static uint screenH;


    public:
     // static void cursorMoved(GLFWwindow* window, double xpos, double ypos);
      static void init(uint screenW, uint screenH, const char* title);
      static GLFWwindow* getGLFWWindow();
      static float getAspectRatio();
      static uint getHeight();
      static uint getWidth();
      
      
  };
}

#endif
