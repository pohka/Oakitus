#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <oak/ecs/entity.h>

#include <vector>
#include <queue>
#include <string>
#include <oak/ui/font.h>
#include <oak/assets/texture.h>
#include <oak/assets/shader.h>
#include <oak/assets/asset.h>
#include <oak/scene/precache.h>

namespace oak
{
  class Shader;
  class Texture;

  //Management of all data from loaded files such as Textures and Shaders
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
      static const char ENGINE_RESOURCES_ROOT_PATH[];
      static std::string rootPath;

      //returns the id
      static uint addShader(std::string name, bool isEngineAsset = false);
      static uint addTexture(std::string name, bool isEngineAsset = false);
      static uint addFont(std::string name, bool isEngineAsset = false);

      static Shader* getShaderByID(uint id);
      static Shader* getShaderByName(std::string name);
      static Texture* getTextureByID(uint textureID);
      static Texture* getTextureByName(std::string name);
      static Shader* getDefaultShader();
      static Texture* getDefaultTexture();
      static uint getTextureIDByName(std::string name);
      static uint getFontIDByName(std::string fontName);
      static ion::Font* getFontByID(uint id);

      static uint getDefaultShaderID();

      //Returns true if a Texture is already loaded
      static bool isTextureLoaded(std::string name);

      //Returns true if a Shader is already loaded
      static bool isShaderLoaded(std::string name);

      static bool isFontLoaded(std::string name);

      //remove a resource by name, returns true if resource was found and removed
      static bool removeShader(std::string name);
      static bool removeTexture(std::string name);
      static bool removeFont(std::string name);

      static void cache(Precache precache);

  private:
    static void init();
  };
}

#endif