#include "time.h"

using namespace oak;

float Time::timeScale = 1.0f;
float Time::m_deltaTime = 0;
float Time::lastFrame = 0;
int Time::numFrames = 0;
float Time::lastFPSCheck = (float)glfwGetTime();
int Time::fps = 0;
int Time::maxFPS = 60;
float Time::minDeltaTime = 1.0f / maxFPS;
float Time::now = 0.0f;

void Time::update()
{
  
  now = (float)glfwGetTime();

  //calculate delta time
  m_deltaTime = now - lastFrame;
  lastFrame = now;
  
  //track fps
  if (now - lastFPSCheck >= 1.0f)
  {
    float diffTime = now - lastFPSCheck;
    //divide by 2 because of double buffer
    fps = (int)((numFrames/2) / diffTime); 
    numFrames = 0;
    lastFPSCheck = now;
  }
  numFrames++;
}

float Time::deltaTime()
{
  return m_deltaTime;
}

int Time::getFPS()
{
  return fps;
}

int Time::getMaxFPS()
{
  return maxFPS;
}

float Time::getMinDeltaTime()
{
  return minDeltaTime;
}

void Time::init()
{
  lastFrame = (float)glfwGetTime();
}

void Time::setMaxFPS(int max)
{
  Time::maxFPS = max;
  Time::minDeltaTime = 1.0f / maxFPS;
}

float Time::getTimeNow()
{
  return now;
}
