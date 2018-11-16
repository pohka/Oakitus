#include "sprite.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "oakitus.h"
#include "texture.h"

using namespace oak;


Sprite::Sprite(std::string src, int srcX, int srcY, int srcW, int srcH, float displayW, float displayH, unsigned int shaderID)
{
  this->srcX = srcX;
  this->srcY = srcY;
  this->srcW = srcW;
  this->srcH = srcH;
  this->w = displayW;
  this->h = displayH;
  
  if (shaderID != NULL)
  {
    this->shaderID = shaderID;
  }
  else 
  {
    shaderID = Oakitus::defaultShaderID;
  }
  
  this->texture = new Texture(src.c_str());
  
  float xMin = ((float)srcX / texture->getWidth());
  float yMin = ((float)srcY / texture->getHeight());
  float xMax = ((float)(srcX+srcW) / texture->getWidth());
  float yMax = ((float)(srcY+srcH) / texture->getHeight());

  float screenW = 960;
  float screenH = 540;

  float xx = this->w / screenH;
  float yy = this->h / screenH;

  float vertices[] = {
    // positions          // texture coords
    -xx, -yy, 0.0f,  xMin, yMax, //bottom left
     xx, -yy, 0.0f,  xMax, yMax, //bottom right
     xx,  yy, 0.0f,  xMax, yMin, //top right

     xx,  yy, 0.0f,  xMax, yMin, //top right
    -xx,  yy, 0.0f,  xMin, yMin, //top left
    -xx, -yy, 0.0f,  xMin, yMax, //botom left
  };
  
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);

  glBindVertexArray(this->VAO);

  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  
  
}

Sprite::~Sprite()
{
  delete texture;
  glDeleteVertexArrays(1, &this->VAO);
  glDeleteBuffers(1, &this->VBO);
}

std::string Sprite::getSrc()
{
  return this->src;
}

unsigned int Sprite::getVAO()
{
  return this->VAO;
}

void Sprite::onDraw()
{
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->texture->getID());
  glBindVertexArray(this->VAO);

  glm::mat4 model = glm::mat4(1.0);
  glm::vec3 pos(
    entity->position.x - Oakitus::camera->position.x,
    entity->position.y - Oakitus::camera->position.y, 
    entity->position.z
  );
  model = glm::translate(model, pos);

 // model = glm::translate(model, Oakitus::camera->position);

  Shader* shader = Oakitus::findShaderByID(this->shaderID);

  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
  
}