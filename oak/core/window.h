#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "types.h"
#include <glm/glm.hpp>

namespace oak
{
  class Window
  {
    static GLFWwindow* window;
    
    static uint viewportW;
    static uint viewportH;
    static uint windowW;
    static uint windowH;
    static float worldToVPRatio;
    static float vpAspectRatio;
    static float windowToVPRatioX;
    static float windowToVPRatioY;
    static glm::mat4 projectionMatrix;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void updateWindowToVPRatio();

    public:
      static void cursorMoved(GLFWwindow* window, double xpos, double ypos);
      static void init(
        uint viewportW,
        uint viewportH,
        uint windowW,
        uint windowH, 
        const char* title
      );
      static GLFWwindow* getGLFWWindow();
      static float getAspectRatio();
      static uint getHeight();
      static uint getWidth();
      static float worldToViewportCoords(float pixels);
      static glm::mat4& getProjectionMatrix();
      
  };
}

#endif
