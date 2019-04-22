#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>

#include <locale>
#include <oak/lua/lua_script.h>
#include <oak/lua/lua_s.h>
#include <oak/lua/lua_constants.h>
#include <oak/meta/prefab_validator.h>




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
  //possibly change this in future to: scripts/main.lua
  //right now the VS root path for lua is not correct
  //therefore it cant find the scripts when using require() in lua
  //if you open the exe directly with the path: "scripts/main.lua", it will work but not in VS runtime
  std::string initScript;
#ifdef DEBUG_MODE
  initScript = "../Release/scripts/main.lua";
#else
  initScript = "scripts/main.lua";
#endif

  lua_State* L = LuaS::state;

  LuaS::loadFile(initScript);
  LuaS::doFile(initScript);
  lua_getglobal(LuaS::state, LUA_ON_LOAD);
  LuaS::call();
  lua_pop(LuaS::state, 1);
}


void LuaScene::setPrecacheFromMetaData()
{
  auto data = MetaData::getData(META_DATA_KEY_SCENE);

  //reading precache asset names
  if (data["precache"] != nullptr)
  {
    //textures
    if (data["precache"]["textures"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["textures"].size(); i++)
      {
        if (data["precache"]["textures"][i].is_string())
        {
          precache.textures.push_back(data["precache"]["textures"][i]);
        }
      }
    }
    //shaders
    if (data["precache"]["shaders"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["shaders"].size(); i++)
      {
        if (data["precache"]["shaders"][i].is_string())
        {
          precache.shaders.push_back(data["precache"]["shaders"][i]);
        }
      }
    }
    //fonts
    if (data["precache"]["fonts"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["fonts"].size(); i++)
      {
        if (data["precache"]["fonts"][i].is_string())
        {
          precache.fonts.push_back(data["precache"]["fonts"][i]);
        }
      }
    }
  }
}
