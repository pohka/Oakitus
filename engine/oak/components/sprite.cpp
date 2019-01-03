#include "sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <oak/assets/stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <oak/scene/camera.h>
#include <oak/window/window.h>
#include <oak/core/resources.h>

using namespace oak;


Sprite::Sprite(
  std::string src,
  int srcX,
  int srcY,
  int srcW,
  int srcH,
  float displayW,
  float displayH,
  std::string shaderName
) : Component()
{
  this->srcX = srcX;
  this->srcY = srcY;
  this->srcW = srcW;
  this->srcH = srcH;
  this->w = displayW;
  this->h = displayH;
  
  shaderID = Resources::getShaderByName(shaderName)->getID();

  Texture* texture = Resources::getTextureByName(src);
  this->textureID = texture->getID();
  float xMin = ((float)srcX / texture->getWidth());
  float yMin = ((float)srcY / texture->getHeight());
  float xMax = ((float)(srcX + srcW) / texture->getWidth());
  float yMax = ((float)(srcY + srcH) / texture->getHeight());

  construct(xMin, xMax, yMin, yMax);
}

Sprite::Sprite(
  std::string src,
  float displayW,
  float displayH
) : Component(TICK_GROUP_DEFAULT, TICK_TYPE_NOT_TICKABLE, true)
{
  this->w = displayW;
  this->h = displayH;
  this->shaderID = Resources::getDefaultShader()->getID();
  this->textureID = Resources::getTextureIDByName(src);
  construct(0.0f, 1.0f, 0.0f, 1.0f);
}

void Sprite::construct(float xMin, float xMax, float yMin, float yMax)
{
  float xx = Window::worldToViewportCoords(w) * 0.5f;
  float yy = Window::worldToViewportCoords(h) * 0.5f;

  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       xMin, yMax, //bottom left
     xx, -yy,       xMax, yMax, //bottom right
     xx,  yy,       xMax, yMin, //top right

     xx,  yy,       xMax, yMin, //top right
    -xx,  yy,       xMin, yMin, //top left
    -xx, -yy,       xMin, yMax //botom left
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

Sprite::~Sprite()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

std::string Sprite::getSrc() const
{
  return this->src;
}

unsigned int Sprite::getVAO() const
{
  return this->VAO;
}

void Sprite::onRender() const
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(this->VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    Window::worldToViewportCoords(entity->position.x) - camNPos.x,
    Window::worldToViewportCoords(entity->position.y) - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);

  float rotation = entity->rotation.z;
  model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0f));

  Shader* shader = Resources::getShaderByID(this->shaderID);
  shader->use();
  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  
}