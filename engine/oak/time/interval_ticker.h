#pragma once
#ifndef INTERVAL_TICKER_H
#define INTERVAL_TICKER_H

namespace oak
{
  struct IntervalTicker
  {
    IntervalTicker(float interval = 0.0f, bool tickonCreate = false);

    //returns true if it should tick in this frame
    bool onTick();

    void reset(float interval, bool tickonCreate = false);

    float interval = 0.0f;

    private:
      
      float lastTickTime = 0.0f;
  };
}

#endif