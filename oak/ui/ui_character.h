#ifndef UI_CHARACTER_H
#define UI_CHARACTER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

namespace oak
{
  namespace ui
  {
    ///font face character data
    struct Character
    {
      GLuint     textureID;  // ID handle of the glyph texture
      glm::ivec2 size;       // Size of glyph
      glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
      FT_Pos     advance;    // Offset to advance to next glyph
    };
  }
}

#endif
