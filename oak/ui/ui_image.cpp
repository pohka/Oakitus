#include "ui_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include <core/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace oak::ui;
using namespace oak;

UIImage* UIImage::createImage(std::string src, ushort w, ushort h)
{
  UIImage* img = new UIImage();
  img->src = src;
  img->textureID = Resources::getTextureIDBySrc(src);
  img->w = w;
  img->h = h;
 // img->offsetx = 0.0f;
  //img->offset.y = 0.0f;

  glGenVertexArrays(1, &img->VAO);
  glGenBuffers(1, &img->VBO);
  glBindVertexArray(img->VAO);

  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  setImageBuffer(img, windowToVPRatio.x, windowToVPRatio.y);

  const int POS_COORDS = 2;
  const int TEX_COORDS = 2;
  const int TOTAL_SIZEOF = (POS_COORDS * TEX_COORDS) * sizeof(float);

  // position attribute
  glVertexAttribPointer(0, POS_COORDS, GL_FLOAT, GL_FALSE, TOTAL_SIZEOF, (void*)0);
  glEnableVertexAttribArray(0);


  // texture coord attribute
  glVertexAttribPointer(1, POS_COORDS, GL_FLOAT, GL_FALSE, TOTAL_SIZEOF, (void*)(POS_COORDS * sizeof(float)));
  glEnableVertexAttribArray(1);

  return img;
}

void UIImage::setImageBuffer(
  UIImage* img,
  float windowToVPRatioX,
  float windowToVPRatioY
)
{
  float xx = (windowToVPRatioX * Window::worldToViewportCoords((float)img->w)) * 0.5f;
  float yy = (windowToVPRatioY * Window::worldToViewportCoords((float)img->h)) * 0.5f;
  float xMin = 0.0f;
  float xMax = 1.0f;
  float yMin = 0.0f;
  float yMax = 1.0f;

  float vertices[] = {
    // positions    // texture coords
    -xx, -yy,       xMin, yMax, //bottom left
     xx, -yy,       xMax, yMax, //bottom right
     xx,  yy,       xMax, yMin, //top right

     xx,  yy,       xMax, yMin, //top right
    -xx,  yy,       xMin, yMin, //top left
    -xx, -yy,       xMin, yMax //botom left
  };

  glBindBuffer(GL_ARRAY_BUFFER, img->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void UIImage::renderImage(UIImage* img, float parentX, float parentY)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, img->textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(img->VAO);

  glm::mat4 model = glm::mat4(1.0);

  //projection from world pixels to viewport coords to window coords
  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  float worldToVP = Window::worldToViewportCoords(1.0f);
  float projectionX = windowToVPRatio.x * worldToVP;
  float projectionY = windowToVPRatio.y * worldToVP;

  glm::vec3 pos(
    (parentX * Window::getAspectRatio()) + (projectionX * (float)img->offset.x),
    parentY + (projectionY * (float)img->offset.y),
    0.0f
  );
  model = glm::translate(model, pos);

  Shader& shader = Resources::getDefaultShader();
  shader.use();
  shader.setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UIImage::removeImage(UIImage* img)
{
  glDeleteVertexArrays(1, &img->VAO);
  glDeleteBuffers(1, &img->VBO);
}