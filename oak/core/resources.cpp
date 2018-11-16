#include "resources.h"

using namespace oak;

uint Resources::defaultShaderID;

std::vector<Shader*> Resources::shaders;

void Resources::addShader(Shader& shader)
{
  shaders.push_back(&shader);
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