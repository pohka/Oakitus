#include <debug.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "collision_box.h"
#include <cstdlib>

using namespace oak;

CollisionBox::CollisionBox(float offsetX, float offsetY, float width, float height)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  this->w = width;
  this->h = height;
  type = CollisionType::BOX;
}

bool oak::CollisionBox::intersects(CollisionShape &shape) const
{
  if (shape.getType() == CollisionType::BOX)
  {
    CollisionBox* b = static_cast<CollisionBox*>(&shape);

    return (
      std::abs(this->originX() - b->originX()) < (this->w * 0.5f + b->width() * 0.5f) &&
      std::abs(this->originY() - b->originY()) < (this->h * 0.5f + b->height() * 0.5f)
    );
  }

  return false;
}

float CollisionBox::minX() const
{
  return this->entity->position.x + offsetX - (w * 0.5f);
}

float CollisionBox::minY() const
{
  return this->entity->position.y + offsetY - (h * 0.5f);
}

float CollisionBox::maxX() const
{
  return this->entity->position.x + offsetX - (w * 0.5f);
}

float CollisionBox::maxY() const
{
  return this->entity->position.y + offsetY - (h * 0.5f);
}

float CollisionBox::width() const
{
  return w;
}

float CollisionBox::height() const
{
  return h;
}

float CollisionBox::originX() const
{
  return this->entity->position.x + offsetX;
}

float CollisionBox::originY() const
{
  return this->entity->position.x + offsetX;
}

void CollisionBox::onDebugDraw() const
{
  LOG << "drawing debug box";
}