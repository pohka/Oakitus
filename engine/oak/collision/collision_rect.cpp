#include <cstdlib>
#include <oak/window/window.h>
#include <oak/core/resources.h>
#include "collision.h"
#include <oak/oak_def.h>
#include <oak/build_def.h>

using namespace oak;

CollisionRect::CollisionRect(float offsetX, float offsetY, float width, float height)
{
  m_offsetX = offsetX;
  m_offsetY = offsetY;
  this->w = width;
  this->h = height;
  type = Type::RECT;

  textureID = Resources::getTextureIDByName("box.png");
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
  return this->entity->transform->position().x + m_offsetX - (w * 0.5f);
}

float CollisionRect::minY() const
{
  return this->entity->transform->position().y + m_offsetY - (h * 0.5f);
}

float CollisionRect::maxX() const
{
  return this->entity->transform->position().x + m_offsetX + (w * 0.5f);
}

float CollisionRect::maxY() const
{
  return this->entity->transform->position().y + m_offsetY + (h * 0.5f);
}

float CollisionRect::width() const
{
  return w;
}

float CollisionRect::height() const
{
  return h;
}

RectBounds CollisionRect::getRectBounds() const
{
  glm::vec3 pos = this->entity->transform->position();
  RectBounds bounds;
  bounds.minX = pos.x + m_offsetX - (w * 0.5f);
  bounds.minY = pos.y + m_offsetY - (h * 0.5f);
  bounds.maxX = pos.x + m_offsetX + (w * 0.5f);
  bounds.maxY = pos.y + m_offsetY + (h * 0.5f);
  return bounds;
}

void CollisionRect::setWidth(float w)
{
  this->w = w;

#ifdef DEBUG_MODE
  initVAO(w, h);
#endif
}
void CollisionRect::setHeight(float h)
{
  this->h = h;

#ifdef DEBUG_MODE
  initVAO(w, h);
#endif
}
