#ifndef RESOURCES_H
#define RESOURCES_H

#include "entity.h"

#include <vector>
#include <queue>
#include <string>
#include "../ui/font.h"

#include "../fallback.h"

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
    static std::vector<ui::Font*> fonts;
    static FT_Library freeType;


    public:
      static void addShader(std::string shaderName);
      static void addShader(Shader& shader);
      static void addTexture(std::string src);
      static void addTexture(Texture& texture);
      static void addFont(std::string src);
      static void addFont(ui::Font* font);
      static Shader& getShaderByID(uint id);
      static Shader& getShaderByName(std::string name);
      static Texture& getTextureByID(uint textureID);
      static Texture& getTextureBySrc(std::string src);
      static Shader& getDefaultShader();
      static Texture& getDefaultTexture();
      static uint getTextureIDBySrc(std::string src);
      static uchar getFontIDByName(std::string fontName);
      static ui::Font& getFontByID(uchar id);

      ///<summary>Returns true if a Texture is already loaded</summary>
      static bool isTextureLoaded(std::string src);

      ///<summary>Returns true if a Shader is already loaded</summary>
      static bool isShaderLoaded(std::string name);

  private:
    static void init();
  };
}

#endif