#ifndef COLOR_H
#define COLOR_H


namespace oak
{
  namespace ui
  {
    ///rgba color, range: 0.0f to 1.0f
    struct Color
    {
      float r = 0.0f;
      float g = 0.0f;
      float b = 0.0f;
      float a = 1.0f;
    };
  }
}

#endif