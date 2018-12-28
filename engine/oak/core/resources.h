#ifndef RESOURCES_H
#define RESOURCES_H

#include "entity.h"

#include <vector>
#include <queue>
#include <string>
#include <oak/ui/font.h>
#include <oak/core/texture.h>
#include <oak/core/shader.h>
#include <oak/core/asset.h>

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
    static std::vector<ion::Font*> fonts;
    static FT_Library freeType;

    static Texture* defaultTexture;
    static Shader* defaultShader;
    static ion::Font* defaultFont;

    public:
      static std::string rootPath;

      //returns the id
      static uint addShader(std::string shaderName, bool isEngineAsset = false);
      static uint addTexture(std::string src, bool isEngineAsset = false);
      static uint addFont(std::string src, bool isEngineAsset = false);

      static Shader* getShaderByID(uint id);
      static Shader* getShaderByName(std::string name);
      static Texture* getTextureByID(uint textureID);
      static Texture* getTextureBySrc(std::string src);
      static Shader* getDefaultShader();
      static Texture* getDefaultTexture();
      static uint getTextureIDBySrc(std::string src);
      static uint getFontIDByName(std::string fontName);
      static ion::Font* getFontByID(uint id);

      ///<summary>Returns true if a Texture is already loaded</summary>
      static bool isTextureLoaded(std::string name);

      ///<summary>Returns true if a Shader is already loaded</summary>
      static bool isShaderLoaded(std::string name);

      static bool isFontLoaded(std::string name);

  private:
    static void init();
  };
}

#endif