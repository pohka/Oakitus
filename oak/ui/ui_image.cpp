#include "ui_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include <core/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ui_canvas.h"
#include <debug.h>

using namespace ion;
using namespace oak;

UIImage::UIImage(std::string src, ushort w, ushort h) : UINode(UI_NODE_IMAGE)
{
  this->src = src;
  this->textureID = Resources::getTextureIDBySrc(src);
  style->set(STYLE_WIDTH, w);
  style->set(STYLE_HEIGHT, h);
  calcStyle();

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  onWindowResize(windowToVPRatio.x, windowToVPRatio.y);

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

UIImage::~UIImage()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void UIImage::render(UIPoint& nodeCursor)
{
  renderBegin(nodeCursor);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0);

  const UIPoint& projection = UICanvas::getProjection();
  

  glm::vec3 modelPos(
    nodeCursor.x * projection.x,
    nodeCursor.y * projection.y,
    0.0f
  );

  

  model = glm::translate(model, modelPos);

  Shader& shader = Resources::getDefaultShader();
  shader.use();
  shader.setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  UINode::renderEnd(nodeCursor);
}

void UIImage::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{
  //set the image buffers
  float w = cstyle->get(STYLE_WIDTH);
  float h = cstyle->get(STYLE_HEIGHT);
  float xx = (windowToVPRatioX * Window::worldToViewportCoords(w));
  float yy = -(windowToVPRatioY * Window::worldToViewportCoords(h));
  float xMin = 0.0f;
  float xMax = 1.0f;
  float yMin = 0.0f;
  float yMax = 1.0f;

  float vertices[] = {
    // positions    // texture coords
    0, yy,       xMin, yMax, //bottom left
    xx, yy,       xMax, yMax, //bottom right
    xx,  0,       xMax, yMin, //top right

    xx,  0,       xMax, yMin, //top right
    0,  0,       xMin, yMin, //top left
    0, yy,       xMin, yMax //botom left
  };

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void UIImage::setTexture(std::string src)
{
  this->src = src;
  textureID = Resources::getTextureIDBySrc(src);
}