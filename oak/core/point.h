#ifndef POINT_H
#define POINT_H

namespace oak
{
  ///<summary>Simple 2D Point</summary>
  class Point
  {
  public:
    float x;
    float y;

    Point(float x, float y);
    ~Point();
  };
}

#endif