#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

namespace oak
{
  //all time is in seconds
  class Time
  {
    static float lastFrame;
    static float m_deltaTime;
    static int numFrames;
    static int fps;
    static float lastFPSCheck;
    static int maxFPS;
    static float minDeltaTime;

    public:
      static float timeScale;
      static float deltaTime;
      

      static void update();
      static int getFPS();
      static int getMaxFPS();
      static float getMinDeltaTime();
      static float getTimeNow();
      static void init();
      static void setMaxFPS(int max);
      
  };
}

#endif
