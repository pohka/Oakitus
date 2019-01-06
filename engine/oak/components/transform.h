#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <oak/ecs/component.h>


namespace oak
{
  class Transform : public oak::Component
  {
  public:
    Transform();

    //position
    const glm::vec3& position() const;

    void moveBy(float x, float y, float z);
    void moveBy(glm::vec3 amount);

    void moveTo(float x, float y, float z);
    void moveTo(glm::vec3 pos);

    //rotation
    const glm::vec3& rotation() const;

    void rotateBy(float x, float y, float z);
    void rotateBy(glm::vec3 rotation);

    void rotateTo(float x, float y, float z);
    void rotateTo(glm::vec3 rotation);

  private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  };
}

#endif