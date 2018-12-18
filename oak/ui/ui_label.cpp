#include "ui_label.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include "ui_character.h"
#include <core/window.h>
#include "ui_canvas.h"
#include <debug.h>

using namespace oak::ui;
using namespace oak;

UILabel::UILabel(std::string src, ushort fontSize, ushort w, ushort h) : UINode(UI_NODE_LABEL)
{
  this->text = text;
  this->w = w;
  this->h = h;

  this->scale = (float)fontSize / (float)FONT_LOADED_SIZE;
  this->fontID = Resources::getFontIDByName("arial.ttf");

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void UILabel::render()
{
  Shader& shader = Resources::getShaderByName("text");
  // Activate corresponding render state	
  shader.use();
  glUniform4f(
    glGetUniformLocation(shader.getID(), "textColor"),
    color.r, color.g, color.b, color.a
  );
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  
  // Iterate through all characters
  std::string::const_iterator c;

  const Point& projection = UICanvas::getProjection();

  float x = offset.x * projection.x;
  float y = (offset.y - (scale * FONT_LOADED_SIZE))* projection.y;

  Font& font = Resources::getFontByID(fontID);

  Point parentPos = getParentAbsolutePos();
  LOG << "parentPOS:" << parentPos.x << ","<< parentPos.y;

  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = *font.getCharacter(c);

    float bearingX = ch.bearing.x * scale;
    float bearingY = (ch.size.y - ch.bearing.y) * scale;
    GLfloat xpos = (parentPos.x * oak::Window::getAspectRatio()) +(x + projection.x * bearingX);
    GLfloat ypos = parentPos.y + (y - (projection.y * bearingY));

    GLfloat ww = ch.size.x * scale;
    GLfloat hh = ch.size.y * scale;

    float w = projection.x * ww;
    float h = projection.y * hh;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos,     ypos,       0.0, 1.0 },
        { xpos + w, ypos,       1.0, 1.0 },

        { xpos,     ypos + h,   0.0, 0.0 },
        { xpos + w, ypos,       1.0, 1.0 },
        { xpos + w, ypos + h,   1.0, 0.0 }
    };
    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    float advance = (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    x += projection.x * advance;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  UINode::render();
}

void UILabel::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{

}