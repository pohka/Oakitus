#include "font.h"

#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <oak/debug.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <oak/oak_def.h>
#include "ui_def.h"
#include <oak/core/resources.h>

using namespace ion;

uint Font::idCounter = 0;

Font::Font(std::string name, bool isEngineAsset, FT_Library& freetype) : Asset(name, isEngineAsset)
{
  id = idCounter;
  idCounter++;

  std::string fullPath = "";

  if (isEngineAsset)
  {
    fullPath += ENGINE_RESOURCES_ROOT_PATH;
  }
  else
  {
    fullPath += oak::Resources::rootPath;
  }

  fullPath += "fonts/" + name;
  if (FT_New_Face(freetype, fullPath.c_str(), 0, &face))
  {
#ifdef DEBUG_MODE
    LOG_WARNING << "FREETYPE: Failed to load font:" << fullPath;
#endif
  }
  else
  {
    initChars(freetype, this);
  }
}

Font::~Font()
{
  for (std::map<GLchar, Character*>::iterator it = characters.begin(); it != characters.end(); ++it)
  {
    delete it->second;
  }
  characters.clear();
}

Character* Font::getCharacter(std::string::const_iterator& c)
{
  return characters[*c];
}

void Font::initChars(FT_Library& ft, Font* font)
{
  // Set size to load glyphs as
  FT_Set_Pixel_Sizes(font->face, 0, FONT_LOADED_SIZE);

  // Disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load first 128 characters of ASCII set
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph 
    if (FT_Load_Char(font->face, c, FT_LOAD_RENDER))
    {
#ifdef DEBUG_MODE
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
#endif
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
      font->face->glyph->bitmap.width,
      font->face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      font->face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character* character = new Character
    {
        texture,
        glm::ivec2(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows),
        glm::ivec2(font->face->glyph->bitmap_left, font->face->glyph->bitmap_top),
        font->face->glyph->advance.x
    };

    font->characters.insert(std::pair<GLchar, Character*>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  // Destroy FreeType once we're finished
  FT_Done_Face(font->face);
  FT_Done_FreeType(ft);
}

Character* Font::getCharacter(GLchar glChar)
{
  if (characters.find(glChar) != characters.end())
  {
    return characters[glChar];
  }
  return nullptr;
}
