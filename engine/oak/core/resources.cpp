#include "resources.h"
#include <oak/oak_def.h>

#include <oak/build_def.h>
#ifdef DEBUG_MODE
  #include <oak/debug.h>
#endif


using namespace oak;

std::vector<Shader*> Resources::shaders;
std::vector<Texture*> Resources::textures;
std::vector<ion::Font*> Resources::fonts;
Texture* Resources::defaultTexture = nullptr;
Shader* Resources::defaultShader = nullptr;
ion::Font* Resources::defaultFont = nullptr;

FT_Library Resources::freeType;

std::string Resources::rootPath = "";
const char Resources::ENGINE_RESOURCES_ROOT_PATH[] = "../../resources/";

void Resources::init()
{
  //collision shape textures
  addTexture("box.png", true);
  addTexture("circle.png", true);
  uint defaultTexID = addTexture("default.png", true);
  defaultTexture = getTextureByID(defaultTexID);


  uint defaultShaderID = addShader("default", true);
  defaultShader = Resources::getShaderByID(defaultShaderID);

  //default font
  addShader("text", true);

#ifdef DEBUG_MODE
  if (FT_Init_FreeType(&freeType))
  {
    LOG_WARNING << "ERROR::FREETYPE: Could not init FreeType Library";
  }
  else
  {
    LOG << "--LOADED--| FreeType";
  }
#endif

  uint defaultFontID = addFont("arial.ttf", ENGINE_RESOURCES_ROOT_PATH);
  defaultFont = getFontByID(defaultFontID);
}

uint Resources::addShader(const std::string& name, bool isEngineAsset)
{
  if (isEngineAsset || !isShaderLoaded(name))
  {
    Shader* s = new Shader(name, isEngineAsset);
    shaders.push_back(s);
    return s->getID();
  }
#ifdef DEBUG_MODE
  LOG_WARNING << "Shader already loaded: '" << name << "'";
#endif

  return defaultShader->getID();
}

uint Resources::addTexture(const std::string& name, bool isEngineAsset)
{
  if (isEngineAsset || !isTextureLoaded(name))
  {
    Texture* t = new Texture(name, isEngineAsset);
    textures.push_back(t);
    return t->getID();
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "Texture already loaded: '" << name << "'";
#endif

  return defaultTexture->getID();
}

uint Resources::addFont(const std::string& name, bool isEngineAsset)
{
  if (isEngineAsset || !isFontLoaded(name))
  {
    ion::Font* font = new ion::Font(name, isEngineAsset, freeType);
    fonts.push_back(font);
    return font->getID();
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "Font already loaded: '" << name << "'";
#endif

  return defaultFont->getID();
}


uint Resources::getFontIDByName(const std::string& name)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getName() == name)
    {
      return fonts[i]->getID();
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "Font not found with name: '" << name << "'";
#endif

  return defaultFont->getID();
}

ion::Font* Resources::getFontByID(uint id)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getID() == id)
    {
      return fonts[i];
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "FALLBACK | Font id '" << id << "' was not found";
#endif

  return defaultFont;
}

bool Resources::isTextureLoaded(const std::string& name)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (!textures[i]->getIsEngineAsset() && textures[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

bool Resources::isShaderLoaded(const std::string& name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (!shaders[i]->getIsEngineAsset() && shaders[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

bool Resources::isFontLoaded(const std::string& name)
{
  for (uint i = 0; i < fonts.size(); i++)
  {
    if (!fonts[i]->getIsEngineAsset() && fonts[i]->getName() == name)
    {
      return true;
    }
  }
  return false;
}

Shader* Resources::getShaderByID(uint id)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    //LOG << "---";
    //LOG << "id:" << shaders[i]->getID();
    if (shaders[i]->getID() == id)
    {
      
      return shaders[i];
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "FALLBACK | Shader id '" << id << "' was not found";
#endif

  return defaultShader;
}


Shader* Resources::getShaderByName(const std::string& name)
{
  for (uint i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName().compare(name) == 0)
    {
      return shaders[i];
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "FALLBACK | Shader name '" << name << "' was not found";
#endif

  return defaultShader;
}

Texture* Resources::getTextureByID(uint textureID)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getID() == textureID)
    {
      return textures[i];
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "FALLBACK | Texture ID '" << textureID << "' was not found";
#endif

  return defaultTexture;
}

Texture* Resources::getTextureByName(const std::string& src)
{
  for (uint i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getName().compare(src) == 0)
    {
      return textures[i];
    }
  }

#ifdef DEBUG_MODE
  LOG_WARNING << "FALLBACK | Texture src '" << src << "' was not found";
#endif

  return defaultTexture;
}

Shader* Resources::getDefaultShader()
{
  return defaultShader;
}

Texture* Resources::getDefaultTexture()
{
  return defaultTexture;
}

uint Resources::getTextureIDByName(const std::string& name)
{
  return Resources::getTextureByName(name)->getID();
}

uint Resources::getDefaultShaderID()
{
  return defaultShader->getID();
}

bool Resources::removeShader(const std::string& name)
{
  for (unsigned int i = 0; i < shaders.size(); i++)
  {
    if (shaders[i]->getName() == name && !fonts[i]->getIsEngineAsset())
    {
      delete shaders[i];
      shaders.erase(shaders.begin() + i);
      return true;
    }
  }

  return false;
}
bool Resources::removeTexture(const std::string& name)
{
  for (unsigned int i = 0; i < textures.size(); i++)
  {
    if (textures[i]->getName() == name && !fonts[i]->getIsEngineAsset())
    {
      delete textures[i];
      textures.erase(textures.begin() + i);
      return true;
    }
  }

  return false;
}

bool Resources::removeFont(const std::string& name)
{
  for (unsigned int i = 0; i < fonts.size(); i++)
  {
    if (fonts[i]->getName() == name && !fonts[i]->getIsEngineAsset())
    {
      delete fonts[i];
      fonts.erase(fonts.begin() + i);
      return true;
    }
  }

  return false;
}

void Resources::cache(Precache precache)
{
  //TEXTURES
  //----------------------------------
  //delete loaded textures if they are not being used in precache
  unsigned int a = 0;
  while(a < textures.size())
  {
    if (textures[a]->getIsEngineAsset())
    {
      a++;
    }
    else 
    {
      unsigned int index = precache.getIndex(precache.textures, textures[a]->getName());
      //texture is already loaded
      if (index != Precache::NULL_INDEX)
      {
        precache.textures.erase(precache.textures.begin() + index);
        a++;
      }
      //texture is not defined in precache, so delete it
      else
      {
        delete textures[a];
        textures.erase(textures.begin() + a);
      }
    }
  }

  //load new textures
  for (std::string& name : precache.textures)
  {
    addTexture(name);
  }

  //SHADERS
  //----------------------------------
  //delete loaded shaders if they are not being used in precache
  a = 0;
  while (a < shaders.size())
  {
    if (shaders[a]->getIsEngineAsset())
    {
      a++;
    }
    else
    {
      unsigned int index = precache.getIndex(precache.shaders, shaders[a]->getName());
      //texture is already loaded
      if (index != Precache::NULL_INDEX)
      {
        precache.shaders.erase(precache.shaders.begin() + index);
        a++;
      }
      //shader is not defined in precache, so delete it
      else
      {
        delete shaders[a];
        shaders.erase(shaders.begin() + a);
      }
    }
  }

  //load new shaders
  for (std::string& name : precache.shaders)
  {
    addShader(name);
  }


  //FONTS
  //----------------------------------
  //delete loaded shaders if they are not being used in precache
  a = 0;
  while (a < fonts.size())
  {
    if (fonts[a]->getIsEngineAsset())
    {
      a++;
    }
    else
    {
      unsigned int index = precache.getIndex(precache.fonts, fonts[a]->getName());
      //texture is already loaded
      if (index != Precache::NULL_INDEX)
      {
        precache.fonts.erase(precache.fonts.begin() + index);
        a++;
      }
      //shader is not defined in precache, so delete it
      else
      {
        delete shaders[a];
        fonts.erase(fonts.begin() + a);
      }
    }
  }

  //load new shaders
  for (std::string& name : precache.fonts)
  {
    addFont(name);
  }
}