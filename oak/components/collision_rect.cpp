#include <debug.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <core/window.h>
#include <core/camera.h>
#include <core/shader.h>
#include <core/resources.h>
#include "collision.h"

using namespace oak;

CollisionRect::CollisionRect(float offsetX, float offsetY, float width, float height)
{
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  this->w = width;
  this->h = height;
  type = CollisionShape::RECT;

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

bool CollisionRect::intersects(const CollisionRect &shape) const
{
  return Collision::checkRectRect(*this, shape);
}

bool CollisionRect::intersects(const CollisionCircle &shape) const
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
  return this->entity->position.x + offsetX - (w * 0.5f);
}

float CollisionRect::maxY() const
{
  return this->entity->position.y + offsetY - (h * 0.5f);
}

float CollisionRect::width() const
{
  return w;
}

float CollisionRect::height() const
{
  return h;
}

//float CollisionRect::originX() const
//{
//  return this->entity->position.x + offsetX;
//}
//
//float CollisionRect::originY() const
//{
//  return this->entity->position.x + offsetX;
//}

void CollisionRect::onDebugDraw() const
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