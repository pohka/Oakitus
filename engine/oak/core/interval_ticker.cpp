#include "interval_ticker.h"
#include "time.h"

using namespace oak;

IntervalTicker::IntervalTicker(float interval, bool tickonCreate)
{
  this->interval = interval;

  if (tickonCreate)
  {
    lastTickTime = 0.0f;
  }
  else
  {
    lastTickTime = Time::getFrameStartTime() + interval;
  }
}

bool IntervalTicker::onTick()
{
  float now = Time::getFrameStartTime();
  if (now > lastTickTime + interval)
  {
    lastTickTime += interval;
    return true;
  }
  return false;
}