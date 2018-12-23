#ifndef COLOR_H
#define COLOR_H


namespace ion
{
  struct Color
  {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;

    bool operator==(const Color& rhs) const
    {
      return 
        rhs.r == r && 
        rhs.g == g &&
        rhs.b == b && 
        rhs.a == a;
    }

    bool operator!=(const Color& rhs) const
    {
      if (
        rhs.r == r &&
        rhs.g == g &&
        rhs.b == b &&
        rhs.a == a
        )
      {
        return false;
      }
      return true;
    }
  };
}

#endif