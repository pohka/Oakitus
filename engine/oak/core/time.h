#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

namespace oak
{
  ///<summary>Useful time functions, all time is in seconds</summary>
  class Time
  {
    friend class Oakitus;

    static float lastFrame;
    static int numFrames;
    static int fps;
    static float lastFPSCheck;
    static int maxFPS;
    static float minDeltaTime;
    static float m_deltaTime; 
    static float now; 


    public:
      static float timeScale; ///<summary>Scale time to speed up or slow down gameplay</summary>
      
      ///<summary>The time since last frame</summary>
      static float deltaTime();
      
      static int getFPS();
      static int getMaxFPS();
      static float getMinDeltaTime();
      static float getTimeNow();
      static void setMaxFPS(int max);
      
  protected:
    static void init();
    static void update();
  };
}

#endif
