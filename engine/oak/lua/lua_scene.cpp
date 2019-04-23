#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>

#include <locale>
#include <oak/components/lua_script.h>
#include <oak/lua/lua_s.h>
#include <oak/lua/lua_constants.h>
#include <oak/meta/prefab_validator.h>
#include <oak/debug.h>

using namespace oak;
using json = nlohmann::json;

LuaScene* LuaScene::scene = nullptr;

LuaScene::LuaScene(const std::string& name) : Scene()
{
  this->name = name;
  MetaData::load(META_DATA_KEY_SCENE, name);
  setPrecacheFromMetaData();
  PrefabValidator::validate();
  LuaScene::scene = this;
}

void LuaScene::onLoad()
{
  std::string initScript = "scripts/main.lua";

  lua_State* L = LuaS::state;

  //call scene file
  LuaS::loadFile(initScript);
  LuaS::doFile(initScript);
  lua_getglobal(LuaS::state, LUA_ON_LOAD);
  LuaS::call();
  lua_pop(LuaS::state, 1);
}


void LuaScene::setPrecacheFromMetaData()
{
  auto data = MetaData::getData(META_DATA_KEY_SCENE);

  //reading precache asset names with validation

  auto it = data.find("precache");
  if (it != data.end() && it.value().is_object())
  {
    //textures
    auto typeIter = it.value().find("textures");
    if (typeIter != it.value().end() && typeIter.value().is_array())
    {
      auto textureNames = typeIter.value();
      for (unsigned int i = 0; i < textureNames.size(); i++)
      {
        if (textureNames[i].is_string())
        {
          precache.textures.push_back(textureNames[i]);
        }
        else
        {
          LOG_WARNING << "Parsing error in precache.fonts, precache can only load from string values";
        }
      }
    }
    else if (typeIter != it.value().end() && typeIter.value().is_array() == false)
    {
      LOG_WARNING << "Parsing error in precache.textures, textures value must be an array of strings";
    }
    //shaders
    typeIter = it.value().find("shaders");
    if (typeIter != it.value().end() && typeIter.value().is_array())
    {
      auto shaderNames = typeIter.value();
      for (unsigned int i = 0; i < shaderNames.size(); i++)
      {
        if (shaderNames[i].is_string())
        {
          precache.shaders.push_back(shaderNames[i]);
        }
        else
        {
          LOG_WARNING << "Parsing error in precache.shaders, precache can only load from string values";
        }
      }
    }
    else if (typeIter != it.value().end() && typeIter.value().is_array() == false)
    {
      LOG_WARNING << "Parsing error in precache.shaders, shaders value must be an array of strings";
    }
    //fonts
    typeIter = it.value().find("fonts");
    if (typeIter != it.value().end() && typeIter.value().is_array())
    {
      auto fontNames = typeIter.value();
      for (unsigned int i = 0; i < fontNames.size(); i++)
      {
        if (fontNames[i].is_string())
        {
          precache.fonts.push_back(fontNames[i]);
        }
        else
        {
          LOG_WARNING << "Parsing error in precache.fonts, precache can only load from string values";
        }
      }
    }
    else if (typeIter != it.value().end() && typeIter.value().is_array() == false)
    {
      LOG_WARNING << "Parsing error in precache.fonts, fonts value must be an array of strings";
    }
  }
  else if (it != data.end() && it.value().is_object() == false)
  {
    LOG_WARNING << "Precache not parsed as it must be an object";
  }
}
