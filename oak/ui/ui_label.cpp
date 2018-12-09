#include "ui_label.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include "ui_character.h"
#include <core/window.h>
#include "ui_canvas.h"

using namespace oak::ui;
using namespace oak;

UILabel* UILabel::createLabel(std::string text, ushort fontSize, ushort w, ushort h)
{
  UILabel* label = new UILabel();
  label->text = text;
  label->w = w;
  label->h = h;

  label->scale = (float)fontSize / (float)FONT_LOADED_SIZE;
  label->fontID = Resources::getFontIDByName("arial.ttf");

  glGenVertexArrays(1, &label->VAO);
  glGenBuffers(1, &label->VBO);
  glBindVertexArray(label->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, label->VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  return label;
}

void UILabel::renderLabel(UILabel* label, float parentX, float parentY)
{
  Shader& shader = Resources::getShaderByName("text");
  // Activate corresponding render state	
  shader.use();
  glUniform4f(
    glGetUniformLocation(shader.getID(), "textColor"),
    label->color.r, label->color.g, label->color.b, label->color.a
  );
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(label->VAO);

  
  // Iterate through all characters
  std::string::const_iterator c;

  const Point& projection = UICanvas::getProjection();

  float x = label->offset.x * projection.x;
  float y = (label->offset.y - (label->scale * FONT_LOADED_SIZE))* projection.y;

  Font& font = Resources::getFontByID(label->fontID);

  for (c = label->text.begin(); c != label->text.end(); c++)
  {
    Character ch = *font.getCharacter(c);

    float bearingX = ch.bearing.x * label->scale;
    float bearingY = (ch.size.y - ch.bearing.y) * label->scale;
    GLfloat xpos = (parentX * oak::Window::getAspectRatio()) +(x + projection.x * bearingX);
    GLfloat ypos = parentY + (y - (projection.y * bearingY));

    GLfloat ww = ch.size.x * label->scale;
    GLfloat hh = ch.size.y * label->scale;

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
    glBindBuffer(GL_ARRAY_BUFFER, label->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    float advance = (ch.advance >> 6) * label->scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    x += projection.x * advance;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}