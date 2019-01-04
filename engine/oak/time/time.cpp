#include "time.h"


using namespace oak;

float Time::timeScale = 1.0f;

FPSLimiter Time::fpslimiter = FPSLimiter();

bool Time::isPaused = false;
Time::Timer Time::gameTimer;
Time::Timer Time::systemTimer;
float Time::lastFrameTime = 0.0f;

void Time::onTick()
{
  systemTimer.now = (float)glfwGetTime();
  systemTimer.deltaTime = systemTimer.now - lastFrameTime;
  lastFrameTime = systemTimer.now;

  if (!isPaused)
  {
    gameTimer.now += systemTimer.deltaTime;
    gameTimer.deltaTime = systemTimer.deltaTime * timeScale;
  }
  else
  {
    gameTimer.deltaTime = 0.0f;
  }
  
  fpslimiter.onTick();
}

float Time::deltaTime()
{
  return gameTimer.deltaTime;
}

float Time::systemDeltaTime()
{
  return systemTimer.deltaTime;
}



void Time::init()
{
  lastFrameTime = (float)glfwGetTime();
}

float Time::getGameTime()
{
  return gameTimer.now;
}

float Time::getSystemTime()
{
  return systemTimer.now;
}

void Time::setIsPaused(const bool isPaused)
{
  Time::isPaused = isPaused;
}

bool Time::getIsPaused()
{
  return isPaused;
}

const FPSLimiter& Time::getFPSLimiter()
{
  return fpslimiter;
}

