#include "bounds.h"
#include <cstdlib>


using namespace oak;

Bounds::Bounds(float x, float y, float w, float h)
{
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;

  this->origin = new Point(
    x + (w * 0.5f),
    y - (h * 0.5f)
  );
}

Bounds::~Bounds()
{
  delete origin;
}

bool Bounds::intersects(Bounds& b)
{
  Point* aOrigin = this->getOrigin();
  Point* bOrigin = b.getOrigin();

  return (
    std::abs(aOrigin->x - bOrigin->x) < (this->w * 0.5f + b.width() * 0.5f) &&
    std::abs(aOrigin->y - bOrigin->y) < (this->h * 0.5f + b.height() * 0.5f)
  );
}

float Bounds::minX()
{
  return x;
}

float Bounds::minY()
{
  return y;
}

float Bounds::maxX()
{
  return x + w;
}

float Bounds::maxY()
{
  return y - h;
}

float Bounds::height()
{
  return h;
}

float Bounds::width()
{
  return w;
}

Point* Bounds::getOrigin()
{
  return origin;
}