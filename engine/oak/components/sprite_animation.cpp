#include "sprite_animation.h"
#include <oak/core/texture.h>
#include <oak/core/shader.h>
#include <oak/core/resources.h>
#include <oak/core/camera.h>
#include <oak/core/time.h>
#include <oak/debug.h>
#include "animator.h"
#include <oak/oak_def.h>
#include <oak/core/window.h>

using namespace oak;

SpriteAnimation::SpriteAnimation(
  std::string src,
  uchar priority,
  uint frameW,
  uint frameH,
  uint displayW,
  uint displayH,
  float frameDuration,
  std::string shaderName,
  uint totalFrameCount,
  uint startFrameY,
  bool isLooping,
  bool isOnHeap
)
{
  Texture* texture = Resources::getTextureByName(src);
  this->textureID = texture->getID();
  this->shaderID = Resources::getShaderByName(shaderName)->getID();
  this->frameW = frameW;
  this->frameH = frameH;
  this->displayH = displayH;
  this->displayW = displayW;
  this->frameDuration = frameDuration;
  this->startFrameY = startFrameY;
  this->totalFrameCount = totalFrameCount;
  this->curFrameCount = 0;
  this->totalAnimDuration = totalFrameCount * frameDuration;
  this->isLooping = isLooping;
  this->priority = priority;

  this->curFrameX = 0;
  this->curFrameY = startFrameY;

  maxFramesX = texture->getWidth() / frameW;
  maxFramesY = texture->getHeight() / frameH;

  if (isOnHeap)
  {
    load();
  }
}

void SpriteAnimation::load()
{
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  setFrame(ANIM_DIRECTION_RIGHT);
  setVertexAttrs();

  lastFrameTime = Time::getTimeNow();
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

void SpriteAnimation::reset()
{
  curFrameX = 0;
  curFrameY = startFrameY;
  curFrameCount = 0;
  setFrame(ANIM_DIRECTION_RIGHT);
  lastFrameTime = Time::getTimeNow();
}

bool SpriteAnimation::onTick(uchar direction, bool hasChangedDirection)
{
  bool hasAnimEnded = false;

  float now = Time::getTimeNow();
  if (now - lastFrameTime > frameDuration)
  {
    curFrameCount++;
    if (curFrameCount == totalFrameCount)
    {
      curFrameX = 0;
      curFrameY = startFrameY;
      curFrameCount = 0;
      hasAnimEnded = true;
    }
    else
    {
      if (curFrameX + 1 < maxFramesX)
      {
        curFrameX++;
      }
      else
      {
        curFrameX = 0;
        if (curFrameY <= maxFramesY)
        {
          curFrameY += 1;
        }
        else
        {
          curFrameY = 0;
        }
      }
    }
    
    //LOG << "here";
    //LOG << "new frame: " << curFrameX << ", " << curFrameY;

    setFrame(direction);
    lastFrameTime = Time::getTimeNow();

    
  }
  //if on same frame but the direction has changed
  else if (hasChangedDirection)
  {
    setFrame(direction);
  }

  if (isLooping)
  {
    return false;
  }

  return hasAnimEnded;
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

  float rotation = this->animator->entity->rotation.z;
  model = glm::rotate(model, rotation, glm::vec3(0.0, 0.0, 1.0f));


  Shader* shader = Resources::getShaderByID(this->shaderID);
  shader->use();
  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteAnimation::setFrame(uchar direction)
{
  Texture* texture = Resources::getTextureByID(textureID);
  
  float xx = Window::worldToViewportCoords((float)displayW) * 0.5f;
  float yy = Window::worldToViewportCoords((float)displayH) * 0.5f;

  

  

  float xMin = (float)(curFrameX * frameW)/ texture->getWidth();
  float xMax = (float)((curFrameX+1) * frameW) / texture->getWidth();

  //flip x
  if (direction == ANIM_DIRECTION_LEFT)
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

float SpriteAnimation::getTotalAnimDuration() const
{
  return totalAnimDuration;
}

uchar SpriteAnimation::getPriority() const
{
  return priority;
}
