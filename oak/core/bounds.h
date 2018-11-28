#ifndef BOUNDS_H
#define BOUNDS_H

#include "point.h"

namespace oak
{
  class Bounds
  {
    float x;
    float y;
    float w;
    float h;
    Point* origin;

    public:
      Bounds(float x, float y, float w, float h);
      ~Bounds();

      float minX() const;
      float minY() const;
      float maxX() const;
      float maxY() const;
      float height() const;
      float width() const;
      bool intersects(Bounds& b) const;
      Point* getOrigin() const;
  };
}

#endif