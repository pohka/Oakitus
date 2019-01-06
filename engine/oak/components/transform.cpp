#include "transform.h"
#include <oak/ecs/entity.h>

using namespace oak;

Transform::Transform() : Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, false)
{

}

//position
//-----------------------------------

const glm::vec3& Transform::position() const
{
  return m_position;
}

void Transform::moveBy(float x, float y, float z)
{
  glm::vec3 amount = glm::vec3(x, y, z);
  m_position += amount;


  for (Entity* child : this->entity->children)
  {
    child->transform->moveBy(amount);
  }
}

void Transform::moveBy(glm::vec3 amount)
{
  m_position += amount;
  for (Entity* child : this->entity->children)
  {
    child->transform->moveBy(amount);
  }
}

void Transform::moveTo(float x, float y, float z)
{
  glm::vec3 diff = glm::vec3(
    x - m_position.x,
    y - m_position.y,
    z - m_position.z
  );

  m_position.x = x;
  m_position.y = y;
  m_position.z = z;

  for (Entity* child : this->entity->children)
  {
    child->transform->moveBy(diff);
  }
}

void Transform::moveTo(glm::vec3 pos)
{
  glm::vec3 diff = pos - m_position;
  m_position = pos;

  for (Entity* child : this->entity->children)
  {
    child->transform->moveBy(diff);
  }
}


//rotation
//---------------------------------

const glm::vec3& Transform::rotation() const
{
  return m_rotation;
}

void Transform::rotateBy(float x, float y, float z)
{
  glm::vec3 amount = glm::vec3(x, y, z);
  m_rotation += amount;


  for (Entity* child : this->entity->children)
  {
    child->transform->rotateBy(amount);
  }
}

void Transform::rotateBy(glm::vec3 amount)
{
  m_rotation += amount;
  for (Entity* child : this->entity->children)
  {
    child->transform->rotateBy(amount);
  }
}

void Transform::rotateTo(float x, float y, float z)
{
  glm::vec3 diff = glm::vec3(
    x - m_rotation.x,
    y - m_rotation.y,
    z - m_rotation.z
  );

  m_rotation.x = x;
  m_rotation.y = y;
  m_rotation.z = z;

  for (Entity* child : this->entity->children)
  {
    child->transform->rotateBy(diff);
  }
}

void Transform::rotateTo(glm::vec3 rot)
{
  glm::vec3 diff = rot - m_rotation;

  m_rotation = rot;

  for (Entity* child : this->entity->children)
  {
    child->transform->rotateBy(diff);
  }
}