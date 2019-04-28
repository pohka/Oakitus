#include "sprite_animation.h"
#include <oak/assets/texture.h>
#include <oak/assets/shader.h>
#include <oak/core/resources.h>
#include <oak/scene/camera.h>
#include <oak/time/time.h>
#include "animator.h"
#include <oak/oak_def.h>
#include <oak/window/window.h>


using namespace oak;

SpriteAnimation::SpriteAnimation(
  std::string src,
  uchar priority,
  uint frameW,
  uint frameH,
  uint displayW,
  uint displayH,
  float frameDuration,
  uint shaderID,
  uint totalFrameCount,
  uint startFrameY,
  bool isLooping
)
{
  Texture* texture = Resources::getTextureByName(src);
  this->textureID = texture->getID();
  this->shaderID = shaderID;
  this->frameW = frameW;
  this->frameH = frameH;
  this->displayH = displayH;
  this->displayW = displayW;
  this->frameDuration = frameDuration;
  this->startFrameY = startFrameY;
  this->totalFrameCount = totalFrameCount;
  this->isLooping = isLooping;
  this->priority = priority;

  this->curFrameX = 0;
  this->curFrameY = startFrameY;

  maxFramesX = texture->getWidth() / frameW;
  maxFramesY = texture->getHeight() / frameH;

  load();
}

void SpriteAnimation::load()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  setFrame(0, AnimDirection::RIGHT);
  setVertexAttrs();
}

//setup of vertex attributes layout
void SpriteAnimation::setVertexAttrs() const
{
  const int POS_COORDS = 2;
  const int TEX_COORDS = 2;
  const int TOTAL_SIZEOF = (POS_COORDS * TEX_COORDS) * sizeof(float);

  // position attribute
  glVertexAttribPointer(0, POS_COORDS, GL_FLOAT, GL_FALSE, TOTAL_SIZEOF, (void*)0);
  glEnableVertexAttribArray(0);


  // texture coord attribute
  glVertexAttribPointer(1, POS_COORDS, GL_FLOAT, GL_FALSE, TOTAL_SIZEOF, (void*)(POS_COORDS * sizeof(float)));
  glEnableVertexAttribArray(1);
}

SpriteAnimation::~SpriteAnimation()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void SpriteAnimation::onRender(float positionX, float positionY) const
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 camNPos = Camera::getNormalizedPos();

  glm::vec3 pos(
    Window::worldToViewportCoords(positionX) - camNPos.x,
    Window::worldToViewportCoords(positionY) - camNPos.y,
    0.0f
  );
  model = glm::translate(model, pos);

  float rotation = this->animator->entity->transform->rotation().z;
  model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0f));

  Shader* shader = Resources::getShaderByID(this->shaderID);
  shader->use();
  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteAnimation::setFrame(const uint frameIndex, const AnimDirection direction)
{
  curFrameX = frameIndex % maxFramesX;
  curFrameY = startFrameY + (frameIndex / maxFramesX);

  Texture* texture = Resources::getTextureByID(textureID);
  
  float xx = Window::worldToViewportCoords((float)displayW) * 0.5f;
  float yy = Window::worldToViewportCoords((float)displayH) * 0.5f;

  float xMin = (float)(curFrameX * frameW)/ texture->getWidth();
  float xMax = (float)((curFrameX+1) * frameW) / texture->getWidth();

  //flip x
  if (direction == AnimDirection::LEFT)
  {
    float tmp = xMin;
    xMin = xMax;
    xMax = tmp;
  }

  float yMin = (float)(curFrameY * frameH) / texture->getHeight();
  float yMax = (float)((curFrameY + 1) * frameH) / texture->getHeight();


  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       xMin, yMax, //bottom left
     xx, -yy,       xMax, yMax, //bottom right
     xx,  yy,       xMax, yMin, //top right

     xx,  yy,       xMax, yMin, //top right
    -xx,  yy,       xMin, yMin, //top left
    -xx, -yy,       xMin, yMax //botom left
  };

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}


uchar SpriteAnimation::getPriority() const
{
  return priority;
}

float SpriteAnimation::getFrameDuration() const
{
  return frameDuration;
}

uint SpriteAnimation::getFrameCount() const
{
  return totalFrameCount;
}

bool SpriteAnimation::getIsLooping() const
{
  return isLooping;
}