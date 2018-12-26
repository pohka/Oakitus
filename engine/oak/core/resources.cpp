#include "resources.h"
#include "../oak_def.h"
#include <oak/debug.h>


using namespace oak;

std::vector<Shader*> Resources::shaders;
std::vector<Texture*> Resources::textures;
std::vector<ion::Font*> Resources::fonts;
Texture* Resources::defaultTexture = nullptr;
Shader* Resources::defaultShader = nullptr;

FT_Library Resources::freeType;

std::string Resources::rootPath = "";

void Resources::init()
{
  //collision shape textures
  addTexture("box.png", ENGINE_RESOURCES_ROOT_PATH);
  addTexture("circle.png", ENGINE_RESOURCES_ROOT_PATH);
  defaultTexture = new Texture("default.png", ENGINE_RESOURCES_ROOT_PATH);
  addTexture(*defaultTexture);

  defaultShader = new Shader("default", ENGINE_RESOURCES_ROOT_PATH);
  addShader(*defaultShader);

  //default font
  addShader("text", ENGINE_RESOURCES_ROOT_PATH);

  if (FT_Init_FreeType(&freeType))
  {
    LOG_WARNING << "ERROR::FREETYPE: Could not init FreeType Library";
  }
  else
  {
    LOG << "--LOADED--| FreeType";
  }

  addFont("arial.ttf");
}

void Resources::addShader(std::string shaderName, const std::string& path)
{
  if (!isShaderLoaded(shaderName))
  {
    shaders.push_back(new Shader(shaderName, path));
  }
}

void Resources::addShader(Shader& shader)
{
  shaders.push_back(&shader);
}

void Resources::addTexture(std::string src, const std::string& path)
{
  if (!isTextureLoaded(src))
  {
    textures.push_back(new Texture(src, path));
  }
}

void Resources::addTexture(Texture& texture)
{
  textures.push_back(&texture);
}

void Resources::addFont(std::string src)
{
  ion::Font* font = new ion::Font(src, freeType);
  fonts.push_back(font);
}
void Resources::addFont(ion::Font* font)
{
  fonts.push_back(font);
}

uchar Resources::getFontIDByName(std::string fontName)
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

ion::Font& Resources::getFontByID(uchar id)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getID() == id)
    {
      return *fonts[i];
    }
  }

  LOG_WARNING << "FALLBACK | Font id '" << id << "' was not found";

  return *fonts[0];
}

bool Resources::isTextureLoaded(std::string src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getSrc() == src)
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
    if (shaders[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

Shader& Resources::getShaderByID(uint id)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getID() == id)
    {
      return *shaders[i];
    }
  }
  if (id != defaultShader->getID())
  {
    LOG_WARNING << "FALLBACK | Shader id '" << id << "' was not found";
  }
  return *defaultShader;
}


Shader& Resources::getShaderByName(std::string name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName().compare(name) == 0)
    {
      return *shaders[i];
    }
  }
  if (name != defaultShader->getName())
  {
    LOG_WARNING << "FALLBACK | Shader name '" << name << "' was not found";
  }
  return *defaultShader;
}

Texture& Resources::getTextureByID(uint textureID)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getID() == textureID)
    {
      return *textures[i];
    }
  }
  if (textureID != defaultTexture->getID())
  {
    LOG_WARNING << "FALLBACK | Texture ID '" << textureID << "' was not found";
  }
  return *defaultTexture;
}

Texture& Resources::getTextureBySrc(std::string src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getSrc().compare(src) == 0)
    {
      return *textures[i];
    }
  }
  if (src != defaultTexture->getSrc())
  {
    LOG_WARNING << "FALLBACK | Texture src '" << src << "' was not found";
  }
  return *defaultTexture;
}

Shader& Resources::getDefaultShader()
{
  return *defaultShader;
}

Texture& Resources::getDefaultTexture()
{
  return *defaultTexture;
}

uint Resources::getTextureIDBySrc(std::string src)
{
  return Resources::getTextureBySrc(src).getID();
}