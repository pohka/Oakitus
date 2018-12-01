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
      static Shader& getShaderByID(uint id);
      static Shader& getShaderByName(std::string name);
      static Texture& getTextureByID(uint textureID);
      static Texture& getTextureBySrc(std::string src);
      static Shader& getDefaultShader();
      static Texture& getDefaultTexture();
      static uint getTextureIDBySrc(std::string src);
      static bool isTextureLoaded(std::string src);
      static bool isShaderLoaded(std::string name);
  };
}

#endif