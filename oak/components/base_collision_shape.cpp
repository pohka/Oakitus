#include "base_collision_shape.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <core/window.h>
#include <core/camera.h>
#include <core/shader.h>
#include <core/resources.h>

using namespace oak;

BaseCollisionShape::BaseCollisionShape()
{

}
BaseCollisionShape::~BaseCollisionShape()
{

}

float BaseCollisionShape::originX() const
{
  return this->entity->position.x + offsetX;
}

float BaseCollisionShape::originY() const
{
  return this->entity->position.x + offsetX;
}

void BaseCollisionShape::onDebugDraw() const
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

void BaseCollisionShape::initVAO(float quadW, float quadH)
{
  float xx = Window::worldToViewportCoords(quadW);
  float yy = Window::worldToViewportCoords(quadH);

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