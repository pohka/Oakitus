#pragma once
#ifndef FPS_LIMITER_H
#define FPS_LIMITER_H

namespace oak
{
  //limits FPS
  struct FPSLimiter
  {
    friend class Time;
    friend class Oakitus;

    FPSLimiter();
    ~FPSLimiter();

    //current number of FPS
    int getFPS() const;

    //maximum number of FPS
    int getMaxFPS() const;

    //expected time for a frame
    float getMinDeltaTime() const;

    //set the maximum number of FPS
    void setMaxFPS(const int max);

    //enable or disable FPS limiting
    void setIsLimitingFPS(const bool isLimitingFPS);

    //returns true if limiting FPS
    bool getIsLimitingFPS() const;


  private:
    int numFrames;
    float lastFPSCheck;
    int fps;
    int maxFPS;
    float minDeltaTime;
    bool isLimitingFPS = true;

    //update fps counting
    void onTick();

    //sleep to limit fps
    void sleep();
  };
}

#endif