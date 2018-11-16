#ifndef RESOURCES_H
#define RESOURCES_H

#include "entity.h"
#include "shader.h"

#include <vector>
#include <queue>


namespace oak
{
  class Resources
  {
    static std::vector<Shader*> shaders;

    public:
      static void addShader(Shader& shader);
      static Shader* findShaderByID(uint id);
      static Shader* findShaderByName(std::string name);
      static uint defaultShaderID;
  };
}

#endif