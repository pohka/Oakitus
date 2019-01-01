#include "resources.h"
#include <oak/oak_def.h>
#include <oak/debug.h>


using namespace oak;

std::vector<Shader*> Resources::shaders;
std::vector<Texture*> Resources::textures;
std::vector<ion::Font*> Resources::fonts;
Texture* Resources::defaultTexture = nullptr;
Shader* Resources::defaultShader = nullptr;
ion::Font* Resources::defaultFont = nullptr;

FT_Library Resources::freeType;

std::string Resources::rootPath = "";

void Resources::init()
{
  //collision shape textures
  addTexture("box.png", true);
  addTexture("circle.png", true);
  uint defaultTexID = addTexture("default.png", true);
  defaultTexture = getTextureByID(defaultTexID);


  uint defaultShaderID = addShader("default", true);
  defaultShader = Resources::getShaderByID(defaultShaderID);

  //default font
  addShader("text", true);

  if (FT_Init_FreeType(&freeType))
  {
    LOG_WARNING << "ERROR::FREETYPE: Could not init FreeType Library";
  }
  else
  {
    LOG << "--LOADED--| FreeType";
  }

  uint defaultFontID = addFont("arial.ttf", ENGINE_RESOURCES_ROOT_PATH);
  defaultFont = getFontByID(defaultFontID);
}

uint Resources::addShader(std::string name, bool isEngineAsset)
{
  if (isEngineAsset || !isShaderLoaded(name))
  {
    Shader* s = new Shader(name, isEngineAsset);
    shaders.push_back(s);
    return s->getID();
  }

  LOG_WARNING << "Shader already loaded: '" << name << "'";

  return defaultShader->getID();
}

uint Resources::addTexture(std::string name, bool isEngineAsset)
{
  if (isEngineAsset || !isTextureLoaded(name))
  {
    Texture* t = new Texture(name, isEngineAsset);
    textures.push_back(t);
    return t->getID();
  }

  LOG_WARNING << "Texture already loaded: '" << name << "'";

  return defaultTexture->getID();
}

uint Resources::addFont(std::string name, bool isEngineAsset)
{
  if (isEngineAsset || !isFontLoaded(name))
  {
    ion::Font* font = new ion::Font(name, isEngineAsset, freeType);
    fonts.push_back(font);
    return font->getID();
  }

  LOG_WARNING << "Font already loaded: '" << name << "'";

  return defaultFont->getID();
}


uint Resources::getFontIDByName(std::string name)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getName() == name)
    {
      return fonts[i]->getID();
    }
  }

  LOG_WARNING << "Font not found with name: '" << name << "'";

  return defaultFont->getID();
}

ion::Font* Resources::getFontByID(uint id)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getID() == id)
    {
      return fonts[i];
    }
  }

  LOG_WARNING << "FALLBACK | Font id '" << id << "' was not found";

  return defaultFont;
}

bool Resources::isTextureLoaded(std::string name)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (!textures[i]->getIsEngineAsset() && textures[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

bool Resources::isShaderLoaded(std::string name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (!shaders[i]->getIsEngineAsset() && shaders[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

bool Resources::isFontLoaded(std::string name)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (!fonts[i]->getIsEngineAsset() && fonts[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

Shader* Resources::getShaderByID(uint id)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    //LOG << "---";
    //LOG << "id:" << shaders[i]->getID();
    if (shaders[i]->getID() == id)
    {
      
      return shaders[i];
    }
  }

  LOG_WARNING << "FALLBACK | Shader id '" << id << "' was not found";

  return defaultShader;
}


Shader* Resources::getShaderByName(std::string name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName().compare(name) == 0)
    {
      return shaders[i];
    }
  }

  LOG_WARNING << "FALLBACK | Shader name '" << name << "' was not found";

  return defaultShader;
}

Texture* Resources::getTextureByID(uint textureID)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getID() == textureID)
    {
      return textures[i];
    }
  }

  LOG_WARNING << "FALLBACK | Texture ID '" << textureID << "' was not found";

  return defaultTexture;
}

Texture* Resources::getTextureByName(std::string src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getName().compare(src) == 0)
    {
      return textures[i];
    }
  }

  LOG_WARNING << "FALLBACK | Texture src '" << src << "' was not found";

  return defaultTexture;
}

Shader* Resources::getDefaultShader()
{
  return defaultShader;
}

Texture* Resources::getDefaultTexture()
{
  return defaultTexture;
}

uint Resources::getTextureIDByName(std::string name)
{
  return Resources::getTextureByName(name)->getID();
}

uint Resources::getDefaultShaderID()
{
  return defaultShader->getID();
}