#include "ui_canvas.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/resources.h>

#include "ui_image.h"
#include "ui_label.h"
#include <map>
#include <ui/ui_def.h>

#include <debug.h>

using namespace oak::ui;
using namespace oak;

std::map<GLchar, Character> Character::characters;
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
    Character::characters.insert(std::pair<GLchar, Character>(c, character));
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
      UIImage::renderImage(image);
    }
    else if (nodes[i]->nodeType == UI_NODE_LABEL)
    {
      UILabel* label = static_cast<UILabel*>(nodes[i]);
      UILabel::renderLabel(label);
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
      UIImage::setImageBuffer(
        static_cast<UIImage*>(nodes[i]), 
        windowToVPRatioX,
        windowToVPRatioY
      );
    }
  }
}

