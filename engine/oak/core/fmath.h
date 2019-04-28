#pragma once
#ifndef FMATH_H
#define FMATH_H

namespace oak
{
  struct FMath
  {
    static float clamp(float val, const float min, const float max)
    {
      if (val < min)
      {
        val = min;
      }
      else if (val > max)
      {
        val = max;
      }
      return val;
    }

    static int clampInt(int val, const int min, const int max)
    {
      if (val < min)
      {
        val = min;
      }
      else if (val > max)
      {
        val = max;
      }
      return val;
    }
  };
}

#endif