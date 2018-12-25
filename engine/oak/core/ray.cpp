#include "ray.h"

using namespace oak;
using namespace glm;

Ray::Ray(vec3 origin, vec3 direction)
{
  this->origin = origin;
  this->direction = direction;
}

Ray::~Ray()
{
}

vec3 Ray::planeIntersectPoint(vec3 planeNormal, vec3 planePoint)
{
  vec3 diff = origin - planePoint;
  float prod1 = glm::dot(diff, planeNormal);
  float prod2 = glm::dot(direction, planeNormal);
  float prod3 = prod1 / prod2;
  return origin - direction * prod3;
}