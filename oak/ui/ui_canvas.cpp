#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include <core/window.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace oak::ui;

std::vector<UIElement*> UICanvas::elements;
std::vector<UIImage*> UICanvas::imgs;

void UICanvas::render()
{
  for (uint i = 0; i < elements.size(); i++)
  {
    
  }

  for (uint i = 0; i < imgs.size(); i++)
  {
    renderImage(imgs[i]);
  }
}

void UICanvas::addElement(UIElement* element)
{

}

UIImage* UICanvas::createImage(std::string src, ushort w, ushort h)
{
  UIImage* img = new UIImage;
  img->src = src;
  img->textureID = Resources::getTextureIDBySrc(src);
  img->w = w;
  img->h = h;
  img->x = 0.0f;
  img->y = 0.0f;

  glGenVertexArrays(1, &img->VAO);
  glGenBuffers(1, &img->VBO);
  glBindVertexArray(img->VAO);

  float xx = Window::worldToViewportCoords((float)w) * 0.5f;
  float yy = Window::worldToViewportCoords((float)h) * 0.5f;
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

void UICanvas::renderImage(UIImage* img)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, img->textureID);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindVertexArray(img->VAO);

  glm::mat4 model = glm::mat4(1.0);

  glm::vec3 pos(
    (float)((float)img->x / (float)Window::getWidth()),
    (float)((float)img->y / (float)Window::getHeight()),
    0.0f
  );
  model = glm::translate(model, pos);

  Shader& shader = Resources::getDefaultShader();
  shader.use();
  shader.setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void UICanvas::removeImage(UIImage* img)
{
  glDeleteVertexArrays(1, &img->VAO);
  glDeleteBuffers(1, &img->VBO);
}

