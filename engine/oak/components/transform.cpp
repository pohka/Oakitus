#include "transform.h"
#include <oak/ecs/entity.h>

using namespace oak;

Transform::Transform() : Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, false)
{

}

void Transform::onParentSet(const Transform* parent)
{
  //no parent, move to world coords
  if (parent == nullptr)
  {
    m_localPosition += entity->parent->transform->position();
    m_localRotation += entity->parent->transform->rotation();
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
  if (entity->parent != nullptr)
  {
    pos += entity->parent->transform->position();
  }

  return pos;
}

const glm::vec3& Transform::localPosition() const
{
  return m_localPosition;
}

const glm::vec3 Transform::inversePosition(const glm::vec3& pos) const
{
  if (entity->parent == nullptr)
  {
    return pos;
  }
  return pos - entity->parent->transform->position();
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
  m_localPosition = glm::vec3(
    x - m_localPosition.x,
    y - m_localPosition.y,
    z - m_localPosition.z
  );
}

void Transform::moveTo(glm::vec3 pos)
{
  glm::vec3 diff = pos - m_localPosition;
  m_localPosition = pos;
}


//rotation
//---------------------------------

const glm::vec3 Transform::rotation() const
{
  glm::vec3 rot = m_localRotation;
  if (entity->parent != nullptr)
  {
    rot += entity->parent->transform->rotation();
  }

  return rot;
}

const glm::vec3& Transform::localRotation() const
{
  return m_localRotation;
}

const glm::vec3 Transform::inverseRotation(const glm::vec3& rot) const
{
  if (entity->parent == nullptr)
  {
    return rot;
  }
  return rot - entity->parent->transform->position();
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
  m_localRotation = glm::vec3(
    x - m_localRotation.x,
    y - m_localRotation.y,
    z - m_localRotation.z
  );
}

void Transform::rotateTo(glm::vec3 rot)
{
  m_localRotation = rot;
}