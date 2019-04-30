#pragma once
#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <oak/core/types.h>
#include <glm/glm.hpp>

namespace oak
{
  //Window class, only one window
  class Window
  {
    friend class Oakitus;

    static GLFWwindow* window; //GL window
    
    //Prefered pixel resolution
    static uint viewportW; //Pixel width of the viewport
    static uint viewportH; //Pixel height of the viewport

    //Current size of the window
    static uint windowW; //Current window height
    static uint windowH; //Current window width

    
    static float worldToVPRatio; //Ratio of world to normalized viewport coordinates
    static float vpAspectRatio; //Aspect ratio of the viewport

    //ratio of viewport to window coordinates
    static float windowToVPRatioX; //Ratio of viewport to window coordinates on the x-axis
    static float windowToVPRatioY; //Ratio of viewport to window coordinates on the y-axis

    //projection matrix of the viewport
    static glm::mat4 projectionMatrix; //Projection matrix of the viewport

    //Scrolling event, callback function
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    //Updates the window to viewport ratios for when the window gets resized
    static void updateWindowToVPRatio();

    //Cursor moved event, callback function
    static void cursorMoved(GLFWwindow* window, double xpos, double ypos);

    public:
      //Returns the GL window
      static GLFWwindow* getGLFWWindow();

      //Returns the aspect ratio of the viewport
      static float getAspectRatio();

      //Returns the height of the viewport in pixels
      static uint getHeight();

      //Returns the width of the viewport in pixels
      static uint getWidth();

      //Converts world to normalized viewport coordinates
      static float worldToViewportCoords(float pixels);

      //returns the projection matrix for the viewport
      static glm::mat4& getProjectionMatrix();

      static glm::vec2 getWindowToVPRatio();

      //returns ratio of normalized window to pixel size window unit
      static glm::vec2 getWindowUnitToPixel();

      static void close();
      
    protected:
      //Initialized the window
      static void init(
        uint viewportW,
        uint viewportH,
        uint windowW,
        uint windowH,
        const char* title,
        bool isFullscreen
      );
  };
}

#endif
