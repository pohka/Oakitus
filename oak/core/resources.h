#ifndef RESOURCES_H
#define RESOURCES_H

#include "entity.h"
#include "shader.h"

#include <vector>
#include <queue>
#include <string>

#include "texture.h"

namespace oak
{
  class Resources
  {
    friend class Oakitus;
    static std::vector<Shader*> shaders;
    static std::vector<Texture*> textures;
    static Shader* defaultShader;
    static Texture* defaultTexture;


    public:
      const static std::string PATH;
      static void addShader(Shader& shader);
      static void addTexture(std::string src);
      static Shader* findShaderByID(uint id);
      static Shader* findShaderByName(std::string name);
      static Texture* findTextureByID(uint textureID);
      static Texture * findTextureBySrc(std::string src);
      static Shader& getDefaultShader();
      static Texture& getDefaultTexture();
      static uint getTextureIDBySrc(std::string src);
  };
}

#endif