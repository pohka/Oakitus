#pragma once
#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <oak/core/types.h>
#include <glm/glm.hpp>

namespace oak
{
  ///<summary>Window class, only one window</summary>
  class Window
  {
    friend class Oakitus;

    static GLFWwindow* window; ///<summary>GL window</summary>
    
    //Prefered pixel resolution
    static uint viewportW; ///<summary>Pixel width of the viewport</summary>
    static uint viewportH; ///<summary>Pixel height of the viewport</summary>

    //Current size of the window
    static uint windowW; ///<summary>Current window height</summary>
    static uint windowH; ///<summary>Current window width</summary>

    
    static float worldToVPRatio; ///<summary>Ratio of world to normalized viewport coordinates</summary>
    static float vpAspectRatio; ///<summary>Aspect ratio of the viewport</summary>

    //ratio of viewport to window coordinates
    static float windowToVPRatioX; ///<summary>Ratio of viewport to window coordinates on the x-axis</summary>
    static float windowToVPRatioY; ///<summary>Ratio of viewport to window coordinates on the y-axis</summary>

    //projection matrix of the viewport
    static glm::mat4 projectionMatrix; ///<summary>Projection matrix of the viewport</summary>

    ///<summary>Scrolling event, callback function</summary>
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    ///<summary>Updates the window to viewport ratios for when the window gets resized</summary>
    static void updateWindowToVPRatio();

    ///<summary>Cursor moved event, callback function</summary>
    static void cursorMoved(GLFWwindow* window, double xpos, double ypos);

    public:
      ///<summary>Returns the GL window</summary>
      static GLFWwindow* getGLFWWindow();

      ///<summary>Returns the aspect ratio of the viewport</summary>
      static float getAspectRatio();

      ///<summary>Returns the height of the viewport in pixels</summary>
      static uint getHeight();

      ///<summary>Returns the width of the viewport in pixels</summary>
      static uint getWidth();

      ///<summary>Converts world to normalized viewport coordinates</summary>
      static float worldToViewportCoords(float pixels);

      ///<summary>returns the projection matrix for the viewport</summary>
      static glm::mat4& getProjectionMatrix();

      static glm::vec2 getWindowToVPRatio();

      ///returns ratio of normalized window to pixel size window unit
      static glm::vec2 getWindowUnitToPixel();

      static void close();
      
    protected:
      ///<summary>Initialized the window</summary>
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
