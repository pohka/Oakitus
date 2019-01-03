#include "interval_ticker.h"
#include "time.h"
#include <oak/debug.h>

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
    lastTickTime = Time::getGameTime();
  }
}

bool IntervalTicker::onTick()
{
  float now = Time::getGameTime();
  if (now >= lastTickTime + interval)
  {
    lastTickTime += interval;
    return true;
  }
  return false;
}

void IntervalTicker::reset(float interval, bool tickonCreate)
{
  this->interval = interval;
  if (tickonCreate)
  {
    lastTickTime = 0.0f;
  }
  else
  {
    lastTickTime = Time::getGameTime();
  }
}