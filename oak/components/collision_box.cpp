#include <debug.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "collision_box.h"
#include <cstdlib>
#include <core/window.h>
#include <core/camera.h>
#include <core/shader.h>
#include <core/resources.h>

using namespace oak;

CollisionBox::CollisionBox(float offsetX, float offsetY, float width, float height)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  this->w = width;
  this->h = height;
  type = CollisionType::BOX;

  float xx = Window::worldToViewportCoords(w);
  float yy = Window::worldToViewportCoords(h);

  float vertices[] = {
       xx,  yy,  // top right
       xx, -yy,  // bottom right
      -xx, -yy,  // bottom left
      -xx,  yy   // top left 
  };

  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

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
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBindVertexArray(this->VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    Window::worldToViewportCoords(entity->position.x + offsetX) - camNPos.x,
    Window::worldToViewportCoords(entity->position.y + offsetY) - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);


  Shader* shader = Resources::findShaderByName("collision");
  shader->use();
  shader->setMat4("model", model);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}