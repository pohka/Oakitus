#include <debug.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <core/window.h>
#include <core/resources.h>
#include "collision.h"
#include <oak_def.h>

using namespace oak;

CollisionRect::CollisionRect(float offsetX, float offsetY, float width, float height)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  this->w = width;
  this->h = height;
  type = COLLISION_SHAPE_RECT;

  textureID = Resources::getTextureIDBySrc("box.png");
  initVAO(w, h);
}

bool CollisionRect::intersectsRect(const CollisionRect &shape) const
{
  return Collision::checkRectRect(*this, shape);
}

bool CollisionRect::intersectsCircle(const CollisionCircle &shape) const
{
  return Collision::checkRectCircle(*this, shape);
}

float CollisionRect::minX() const
{
  return this->entity->position.x + offsetX - (w * 0.5f);
}

float CollisionRect::minY() const
{
  return this->entity->position.y + offsetY - (h * 0.5f);
}

float CollisionRect::maxX() const
{
  return this->entity->position.x + offsetX + (w * 0.5f);
}

float CollisionRect::maxY() const
{
  return this->entity->position.y + offsetY + (h * 0.5f);
}

float CollisionRect::width() const
{
  return w;
}

float CollisionRect::height() const
{
  return h;
}
