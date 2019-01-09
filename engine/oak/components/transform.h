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
    const glm::vec3 position() const;
    const glm::vec3& localPosition() const;
    const glm::vec3 inversePosition(const glm::vec3& pos) const;
    const glm::vec2 position2D() const;


    void moveBy(float x, float y, float z);
    void moveBy(glm::vec3 amount);

    void moveTo(float x, float y, float z);
    void moveTo(glm::vec3 pos);

    //rotation
    const glm::vec3 rotation() const;
    const glm::vec3& localRotation() const;
    const glm::vec3 inverseRotation(const glm::vec3& rot) const;

    void rotateBy(float x, float y, float z);
    void rotateBy(glm::vec3 rotation);

    void rotateTo(float x, float y, float z);
    void rotateTo(glm::vec3 rotation);

    void onParentSet(const Transform* parent);

  private:
    glm::vec3 m_localPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_localRotation = glm::vec3(0.0f, 0.0f, 0.0f);
  };
}

#endif