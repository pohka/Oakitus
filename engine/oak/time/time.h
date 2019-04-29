#pragma once
#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>
#include "fps_limiter.h"

namespace oak
{
  struct FPSLimiter;

  //Useful time functions, all time is in seconds
  class Time
  {
    friend class Oakitus;
    
    struct Timer
    {
      float now = 0.0f;
      float deltaTime = 0.0f;
    };

    static FPSLimiter fpslimiter;
    static Timer gameTimer;
    static Timer systemTimer;
    static bool isPaused;
    static float lastFrameTime;

    public:
      static float timeScale; //Scale time to speed up or slow down gameplay
      
      //The time since last frame
      static float deltaTime();
      static float systemDeltaTime();

      //time since the game started, does not count when the game is paused
      static float getGameTime();

      //get the current real world time
      static float getSystemTime();

      static const FPSLimiter& getFPSLimiter();

      static void setIsPaused(const bool isPaused);
      static bool getIsPaused();
      
    protected:
      static void init();
      static void onTick();
  };
}

#endif
