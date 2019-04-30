#include "fps_limiter.h"
#include "time.h"
#include <thread> 
#include <chrono> 

using namespace oak;

FPSLimiter::FPSLimiter()
{
  numFrames = 0;
  lastFPSCheck = static_cast<float>(glfwGetTime());
  fps = 0;
  maxFPS = 80;
  minDeltaTime = 1.0f / static_cast<float>(maxFPS);
}

FPSLimiter::~FPSLimiter() 
{
}

void FPSLimiter::onTick()
{
  float now = Time::getSystemTime();
  if (now - lastFPSCheck >= 1.0f)
  {
    float diffTime = now - lastFPSCheck;
    //divide by 2 because of double buffer
    fps = static_cast<int>((static_cast<float>(numFrames / 2) / diffTime));
    numFrames = 0;
    lastFPSCheck = now;
  }
  else
  {
    numFrames++;
  }
}

int FPSLimiter::getFPS() const
{
  return fps;
}

int FPSLimiter::getMaxFPS() const
{
  return maxFPS;
}

float FPSLimiter::getMinDeltaTime() const
{
  return minDeltaTime;
}

void FPSLimiter::setMaxFPS(const int max)
{
  maxFPS = max;
  minDeltaTime = 1.0f / static_cast<float>(maxFPS);
}

//sleep to limit fps
void FPSLimiter::sleep()
{
  if (isLimitingFPS && Time::systemDeltaTime() < minDeltaTime)
  {
    int sleepTime = static_cast<int>((minDeltaTime - Time::systemDeltaTime()) * 1000.f);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
  }
}

void FPSLimiter::setIsLimitingFPS(const bool isLimitingFPS)
{
  //reset variables, if enabling fps limiting
  if (this->isLimitingFPS == false && isLimitingFPS)
  {
    numFrames = 0;
    lastFPSCheck = static_cast<float>(glfwGetTime());
    fps = 0;
  }

  this->isLimitingFPS = isLimitingFPS;
}

bool FPSLimiter::getIsLimitingFPS() const
{
  return isLimitingFPS;
}