#ifndef FONT_H
#define FONT_H

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "ui_character.h"
#include <map>
#include <core/types.h>

namespace oak
{
  namespace ui
  {

    class Font
    {
      std::string name;
      FT_Face face;
      uchar id;


      public:
        Font(std::string name, FT_Library& freetype);
        uchar getID();
        std::string getName();
        std::map<GLchar, Character> characters;

    private:
      static void initChars(FT_Library& freetype, Font* font);
      static uchar idCounter;
    };
  }
}

#endif