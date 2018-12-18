#include "ui_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include <core/window.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ui_canvas.h"

using namespace oak::ui;
using namespace oak;

UIImage::UIImage(std::string src, ushort w, ushort h) : UINode(UI_NODE_IMAGE)
{
  this->src = src;
  this->textureID = Resources::getTextureIDBySrc(src);
  this->w = w;
  this->h = h;
  // img->offsetx = 0.0f;
   //img->offset.y = 0.0f;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  setImageBuffer(windowToVPRatio.x, windowToVPRatio.y);

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

void UIImage::setImageBuffer(
  float windowToVPRatioX,
  float windowToVPRatioY
)
{
  float xx = (windowToVPRatioX * Window::worldToViewportCoords((float)w)) * 0.5f;
  float yy = (windowToVPRatioY * Window::worldToViewportCoords((float)h)) * 0.5f;
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

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
}

void UIImage::render(float parentX, float parentY)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(VAO);

  glm::mat4 model = glm::mat4(1.0);

  const Point& projection = UICanvas::getProjection();

  glm::vec3 pos(
    (parentX * Window::getAspectRatio()) + (projection.x * (float)offset.x),
    parentY + (projection.y * (float)offset.y),
    0.0f
  );
  model = glm::translate(model, pos);

  Shader& shader = Resources::getDefaultShader();
  shader.use();
  shader.setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UIImage::remove()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}