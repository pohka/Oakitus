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
  class Shader;
  class Texture;

  ///<summary>Management of all data from loaded files such as Textures and Shaders</summary>
  //all getters will return a default resource if the requested resource does not exist
  class Resources
  {
    friend class Oakitus;

    //containers
    static std::vector<Shader*> shaders;
    static std::vector<Texture*> textures;

    //default resouces
    static Shader* defaultShader;
    static Texture* defaultTexture;


    public:
      const static std::string RESOURCES_ROOT_PATH;

      static void addShader(std::string shaderName);
      static void addTexture(std::string src);
      static Shader& getShaderByID(uint id);
      static Shader& getShaderByName(std::string name);
      static Texture& getTextureByID(uint textureID);
      static Texture& getTextureBySrc(std::string src);
      static Shader& getDefaultShader();
      static Texture& getDefaultTexture();
      static uint getTextureIDBySrc(std::string src);

      ///<summary>Returns true if a Texture is already loaded</summary>
      static bool isTextureLoaded(std::string src);

      ///<summary>Returns true if a Shader is already loaded</summary>
      static bool isShaderLoaded(std::string name);
  };
}

#endif