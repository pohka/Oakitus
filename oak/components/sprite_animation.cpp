#include "sprite_animation.h"
#include <core/texture.h>
#include <core/shader.h>
#include <core/resources.h>
#include <core/camera.h>
#include <core/time.h>
#include <debug.h>

using namespace oak;



SpriteAnimation::SpriteAnimation(
  std::string src,
  uint frameW,
  uint frameH,
  uint displayW,
  uint displayH,
  float frameDuration,
  std::string shaderName,
  uint frameCount,
  uint frameStartX,
  uint frameStartY
)
{
  Texture& texture = Resources::getTextureBySrc(src);
  this->textureID = texture.getID();
  this->shaderID = Resources::getShaderByName(shaderName).getID();
  this->frameW = frameW;
  this->frameH = frameH;
  this->displayH = displayH;
  this->displayW = displayW;
  this->frameDuration = frameDuration;
  this->frameStartX = frameStartX;
  this->frameStartY = frameStartY;
  this->curFrameX = frameStartX;
  this->curFrameY = frameStartY;
  this->frameCount = frameCount;
  this->curFrameCount = 0;

  maxFramesX = texture.getWidth() / frameW;
  maxFramesY = texture.getHeight() / frameH;

  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  setFrame(curFrameX, curFrameY);
}

SpriteAnimation::~SpriteAnimation()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void SpriteAnimation::onUpdate()
{
  float now = Time::getTimeNow();
  if (now - lastFrameTime > frameDuration)
  {
    curFrameCount++;
    if (curFrameCount == frameCount)
    {
      curFrameX = frameStartX;
      curFrameY = frameStartY;
      curFrameCount = 0;
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
    

    LOG << "new frame: " << curFrameX << ", " << curFrameY;

    setFrame(curFrameX, curFrameY);

    lastFrameTime = now;
  }
}

void SpriteAnimation::onDraw() const
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

  Shader* shader = &Resources::getShaderByID(this->shaderID);
  shader->use();
  shader->setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SpriteAnimation::setFrame(uint frameX, uint frameY)
{
  Texture& texture = Resources::getTextureByID(textureID);
  
  float xx = Window::worldToViewportCoords((float)displayW) * 0.5f;
  float yy = Window::worldToViewportCoords((float)displayH) * 0.5f;

  float xMin = (float)(frameX * frameW)/ texture.getWidth();
  float xMax = (float)((frameX+1) * frameW) / texture.getWidth();
  float yMin = (float)(frameY * frameH) / texture.getHeight();
  float yMax = (float)((frameY + 1) * frameH) / texture.getHeight();


  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       xMin, yMax, //bottom left
     xx, -yy,       xMax, yMax, //bottom right
     xx,  yy,       xMax, yMin, //top right

     xx,  yy,       xMax, yMin, //top right
    -xx,  yy,       xMin, yMin, //top left
    -xx, -yy,       xMin, yMax //botom left
  };

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