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

uint Resources::addShader(std::string shaderName, bool isEngineAsset)
{
  if (isEngineAsset || !isShaderLoaded(shaderName))
  {
    Shader* s = new Shader(shaderName, isEngineAsset);
    shaders.push_back(s);
    return s->getID();
  }
  return defaultShader->getID();
}

uint Resources::addTexture(std::string src, bool isEngineAsset)
{
  if (isEngineAsset || !isTextureLoaded(src))
  {
    Texture* t = new Texture(src, isEngineAsset);
    textures.push_back(t);
    return t->getID();
  }
  return defaultTexture->getID();
}

uint Resources::addFont(std::string src, bool isEngineAsset)
{
  if (isEngineAsset || !isFontLoaded(src))
  {
    ion::Font* font = new ion::Font(src, isEngineAsset, freeType);
    fonts.push_back(font);
    return font->getID();
  }

  return defaultFont->getID();
}


uint Resources::getFontIDByName(std::string fontName)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getName() == fontName)
    {
      return fonts[i]->getID();
    }
  }
  LOG_WARNING << "Font not found with name: '" << fontName << "'";

  return 0;
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

  return fonts[0];
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
    if (shaders[i]->getID() == id)
    {
      return shaders[i];
    }
  }
  if (id != defaultShader->getID())
  {
    LOG_WARNING << "FALLBACK | Shader id '" << id << "' was not found";
  }
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
  if (name != defaultShader->getName())
  {
    LOG_WARNING << "FALLBACK | Shader name '" << name << "' was not found";
  }
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
  if (textureID != defaultTexture->getID())
  {
    LOG_WARNING << "FALLBACK | Texture ID '" << textureID << "' was not found";
  }
  return defaultTexture;
}

Texture* Resources::getTextureBySrc(std::string src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getName().compare(src) == 0)
    {
      return textures[i];
    }
  }
  if (src != defaultTexture->getName())
  {
    LOG_WARNING << "FALLBACK | Texture src '" << src << "' was not found";
  }
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

uint Resources::getTextureIDBySrc(std::string src)
{
  return Resources::getTextureBySrc(src)->getID();
}