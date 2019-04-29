#pragma once
#ifndef FONT_H
#define FONT_H

#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "ui_character.h"
#include <map>
#include <oak/core/types.h>
#include <oak/assets/asset.h>

namespace ion
{
  //font class
  class Font : public oak::Asset
  {
    FT_Face face;
    std::map<GLchar, Character*> characters;

    public:
      Font(std::string name, bool isEngineAsset, FT_Library& freetype);
      ~Font();
      Character* getCharacter(std::string::const_iterator& c);
      Character* getCharacter(GLchar glChar);

  private:
    static void initChars(FT_Library& freetype, Font* font);
    static uint idCounter;
      
  };
}

#endif