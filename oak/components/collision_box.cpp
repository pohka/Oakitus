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

  textureID = Resources::findTextureBySrc("box.png")->getID();

  float texMin = 0.0f;
  float texMax = 1.0f;

  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       texMin, texMax, //bottom left
     xx, -yy,       texMax, texMax, //bottom right
     xx,  yy,       texMax, texMin, //top right

     xx,  yy,       texMax, texMin, //top right
    -xx,  yy,       texMin, texMin, //top left
    -xx, -yy,       texMin, texMax //botom left
  };

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);

  glBindVertexArray(this->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
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
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(this->VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    Window::worldToViewportCoords(entity->position.x + offsetX) - camNPos.x,
    Window::worldToViewportCoords(entity->position.y + offsetY) - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);


  Shader* shader = &Resources::getDefaultShader();
  shader->use();
  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}