#include "ui_label.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include "ui_character.h"
#include <core/window.h>
#include "ui_canvas.h"
#include <debug.h>

using namespace ion;
using namespace oak;

UILabel::UILabel(std::string src, float fontSize) : UINode(UI_NODE_LABEL)
{
  this->text = text;
  //this->scale = (float)fontSize / (float)FONT_LOADED_SIZE;
  this->fontID = Resources::getFontIDByName("arial.ttf");

  style.set(STYLE_HEIGHT, fontSize);
  style.set(STYLE_FONT_SIZE, fontSize);

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

void UILabel::render(UIPoint& nodeCursor)
{
  renderBegin(nodeCursor);

  scale = cstyle.attrs[STYLE_FONT_SIZE] / (float)FONT_LOADED_SIZE;

  Shader& shader = Resources::getShaderByName("text");
  // Activate corresponding render state	
  shader.use();
  glUniform4f(
    glGetUniformLocation(shader.getID(), "textColor"),
    cstyle.color.r,
    cstyle.color.g,
    cstyle.color.b,
    cstyle.color.a
  );
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(VAO);

  
  // Iterate through all characters
  std::string::const_iterator c;

  const UIPoint& projection = UICanvas::getProjection();
  UIPoint parentPos = getParentPos();

  //character cursor position
  float chCursorX = 0.0f;
  float chCursorY = (scale * FONT_LOADED_SIZE);

  Font& font = Resources::getFontByID(fontID);

  for (c = text.begin(); c != text.end(); c++)
  {
    Character ch = *font.getCharacter(c);

    float bearingX = ch.bearing.x * scale;
    float bearingY = (ch.size.y - ch.bearing.y) * scale;
    GLfloat xpos = (nodeCursor.x + chCursorX + bearingX) * projection.x;
    GLfloat ypos = (nodeCursor.y - chCursorY - bearingY) * projection.y;

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
    chCursorX += advance;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  UINode::renderEnd(nodeCursor);
}

void UILabel::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{

}