#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>
#include <core/window.h>

#include <debug.h>

using namespace oak::ui;
using namespace oak;

std::map<GLchar, Character> UICanvas::characters;
std::vector<UINode*> UICanvas::nodes;

void UICanvas::init()
{
  Resources::addShader("text");
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
  {
    LOG_WARNING << "ERROR::FREETYPE: Could not init FreeType Library";
  }
  else
  {
    LOG << "WORKING";
  }

  FT_Face face;
  if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
  {
    LOG_WARNING << "ERROR::FREETYPE: Failed to load font";
  }
  else
  {
    LOG << "Font loaded";
    initChars(ft, face);
  }

  
}

void UICanvas::initChars(FT_Library& ft, FT_Face& face)
{
  // Set size to load glyphs as
  FT_Set_Pixel_Sizes(face, 0, 48);

  // Disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load first 128 characters of ASCII set
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph 
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character =
    {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
    };
    characters.insert(std::pair<GLchar, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  // Destroy FreeType once we're finished
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}

void UICanvas::render()
{
  for (uint i = 0; i < nodes.size(); i++)
  {
    if (nodes[i]->nodeType == UI_NODE_IMAGE)
    {
      UIImage* image = static_cast<UIImage*>(nodes[i]);
      renderImage(image);
    }
    else if (nodes[i]->nodeType == UI_NODE_LABEL)
    {
      UILabel* label = static_cast<UILabel*>(nodes[i]);
      renderLabel(label);
    }
  }
}

void UICanvas::onWindowResize(float windowToVPRatioX, float windowToVPRatioY)
{
  //resize all the image nodes
  for (uint i = 0; i < nodes.size(); i++)
  {
    if (nodes[i]->nodeType == UI_NODE_IMAGE)
    {
      setImageBuffer(
        static_cast<UIImage*>(nodes[i]), 
        windowToVPRatioX,
        windowToVPRatioY
      );
    }
  }
}

UIImage* UICanvas::createImage(std::string src, ushort w, ushort h)
{
  UIImage* img = new UIImage();
  img->src = src;
  img->textureID = Resources::getTextureIDBySrc(src);
  img->w = w;
  img->h = h;
  img->x = 0.0f;
  img->y = 0.0f;

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

void UICanvas::setImageBuffer(
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

UILabel* UICanvas::createLabel(std::string text, ushort w, ushort h)
{
  UILabel* label = new UILabel();
  label->text = text;
  label->w = w;
  label->h = h;
  label->color.r = 1.0f;
  label->scale = 1.0f;

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

void UICanvas::renderLabel(UILabel* label)
{
  Shader& shader = Resources::getShaderByName("text");
  // Activate corresponding render state	
  shader.use();
  glUniform3f(
    glGetUniformLocation(shader.getID(), "textColor"), 
    label->color.r, label->color.g, label->color.b
  );
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(label->VAO);

  float x = label->x;
  float y = label->y;

  // Iterate through all characters
  std::string::const_iterator c;

  
  //get projection from font size to viewport to window coords
  glm::vec2 windowToVPRatio = Window::getWindowToVPRatio();
  float worldToVP = Window::worldToViewportCoords(1.0f);
  float projectionX = windowToVPRatio.x * worldToVP;
  float projectionY = windowToVPRatio.y * worldToVP;

  for (c = label->text.begin(); c != label->text.end(); c++)
  {
    Character ch = characters[*c];

    float bearingX = ch.bearing.x * label->scale;
    float bearingY = (ch.size.y - ch.bearing.y) * label->scale;
    GLfloat xpos = x + projectionX * bearingX;
    GLfloat ypos = y - projectionY * bearingY;

    GLfloat ww = ch.size.x * label->scale;
    GLfloat hh = ch.size.y * label->scale;

    float w = projectionX * ww;
    float h = projectionY * hh;

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
    x += projectionX * advance;
  }

  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}