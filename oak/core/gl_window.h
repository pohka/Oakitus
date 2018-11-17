#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "types.h"

namespace oak
{
  class GLWindow
  {
    GLFWwindow* window;
    
    uint windowW;
    uint windowH;


    public:
      uint viewportW;
      uint viewportH;

      GLWindow(uint screenW, uint screenH, const char* title);
      ~GLWindow();
      GLFWwindow* getGLFWWindow();
      float getAspectRatio();
  };
}

#endif
