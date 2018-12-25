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

void Time::update()
{
  //calculate delta time
  float currentFrame = (float)glfwGetTime();
  m_deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
 // m_deltaTime = (float)(1.0f * m_deltaTime);
  
  //track fps
  if (currentFrame - lastFPSCheck >= 1.0f)
  {
    float diffTime = currentFrame - lastFPSCheck;
    //divide by 2 because of double buffer
    fps = (int)((numFrames/2) / diffTime); 
    numFrames = 0;
    lastFPSCheck = currentFrame;
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
  return (float)glfwGetTime();
}