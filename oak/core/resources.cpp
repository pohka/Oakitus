#include "resources.h"

using namespace oak;

Shader* Resources::defaultShader;
Texture* Resources::defaultTexture;

std::vector<Shader*> Resources::shaders;
std::vector<Texture*> Resources::textures;
const std::string Resources::PATH = "res/";

void Resources::addShader(Shader& shader)
{
 // if(!isShaderLoaded)
  shaders.push_back(&shader);
}

void Resources::addTexture(std::string src)
{
  if (!isTextureLoaded(src))
  {
    Texture* tex = new Texture(PATH, src);
    textures.push_back(tex);
  }
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