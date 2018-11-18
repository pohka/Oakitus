#include "resources.h"

using namespace oak;

uint Resources::defaultShaderID;

std::vector<Shader*> Resources::shaders;
std::vector<Texture*> Resources::textures;

void Resources::addShader(Shader& shader)
{
  shaders.push_back(&shader);
}

void Resources::addTexture(std::string src)
{
  if (findTextureBySrc(src) == nullptr)
  {
    Texture* tex = new Texture(src);
    textures.push_back(tex);
  }
}

Shader* Resources::findShaderByID(uint id)
{
  return shaders[0];
}


Shader* Resources::findShaderByName(std::string name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName().compare(name) == 0)
    {
      return shaders[i];
    }
  }
  return nullptr;
}

Texture* Resources::findTextureByID(uint textureID)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getID() == textureID)
    {
      return textures[i];
    }
  }
  return nullptr;
}

Texture* Resources::findTextureBySrc(std::string src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getSrc().compare(src) == 0)
    {
      return textures[i];
    }
  }
  std::cout << "texture not found:" << src << std::endl;
  return nullptr;
}