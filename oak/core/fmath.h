#ifndef FMATH_H
#define FMATH_H

namespace oak
{
  struct FMath
  {
    static void clamp(float& val, float min, float max)
    {
      if (val < min)
      {
        val = min;
      }
      else if (val > max)
      {
        val = max;
      }
    }
  };
}

#endif