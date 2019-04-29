#include "transform.h"
#include <oak/ecs/entity.h>

using namespace oak;

Transform::Transform() : 
  Component(
    Reflect::TRANSFORM,
    Component::TickGroup::DEFAULT,
    TICK_TYPE_NOT_TICKABLE,
    false
  )
{

}

void Transform::onParentSet(const Transform* parent)
{
  //no parent, move to world coords
  if (parent == nullptr)
  {
    m_localPosition += entity->getParent()->transform->position();
    m_localRotation += entity->getParent()->transform->rotation();
  }
  else
  {
    //equivalnt to: current world transform - parent world transform
    m_localPosition = position() - parent->position();
    m_localRotation = rotation() - parent->rotation();
  }
  
}

//position
//-----------------------------------

const glm::vec3 Transform::position() const
{
  glm::vec3 pos = m_localPosition;
  if (entity->getParent() != nullptr)
  {
    pos += entity->getParent()->transform->position();
  }

  return pos;
}

const glm::vec3& Transform::localPosition() const
{
  return m_localPosition;
}

const glm::vec3 Transform::inversePosition(const glm::vec3& pos) const
{
  if (entity->getParent() == nullptr)
  {
    return pos;
  }
  return pos - entity->getParent()->transform->position();
}

const glm::vec2 Transform::position2D() const
{
  glm::vec3 pos = position();
  return glm::vec2(pos.x, pos.y);
}

void Transform::moveBy(float x, float y, float z)
{
  m_localPosition += glm::vec3(x, y, z);
}

void Transform::moveBy(glm::vec3 amount)
{
  m_localPosition += amount;
}

void Transform::moveTo(float x, float y, float z)
{
  m_localPosition.x = x;
  m_localPosition.y = y;
  m_localPosition.z = z;
}

void Transform::moveTo(glm::vec3 pos)
{
  m_localPosition = pos;
}


//rotation
//---------------------------------

const glm::vec3 Transform::rotation() const
{
  glm::vec3 rot = m_localRotation;
  if (entity->getParent() != nullptr)
  {
    rot += entity->getParent()->transform->rotation();
  }

  return rot;
}

const glm::vec3& Transform::localRotation() const
{
  return m_localRotation;
}

const glm::vec3 Transform::inverseRotation(const glm::vec3& rot) const
{
  if (entity->getParent() == nullptr)
  {
    return rot;
  }
  return rot - entity->getParent()->transform->position();
}

void Transform::rotateBy(float x, float y, float z)
{
  m_localRotation += glm::vec3(x, y, z);
}

void Transform::rotateBy(glm::vec3 amount)
{
  m_localRotation += amount;
}

void Transform::rotateTo(float x, float y, float z)
{
  m_localRotation.x = x;
  m_localRotation.y = y;
  m_localRotation.z = z;
}

void Transform::rotateTo(glm::vec3 rot)
{
  m_localRotation = rot;
}