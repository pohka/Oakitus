#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <oak/lua/lua_script.h>
#include <oak/lua/lua_s.h>

using namespace oak;
using json = nlohmann::json;

LuaScene* LuaScene::scene = nullptr;

LuaScene::LuaScene(std::string path) : Scene()
{
  this->path = path;
  std::ifstream i(path + "file.json");
  i >> data;
  if (data != nullptr)
  {
    dataLoaded = true;

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

  luaL_dofile(L, initScript.c_str());
  lua_getglobal(L, "onLoad");
  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    std::cout << "|--LUA_ERROR--|" << " lua_pcall - " << lua_tostring(L, -1) << std::endl;
  }
}

//void LuaScene::logError(lua_State* L, std::string msg)
//{
//  lua_Debug ar;
//  lua_getstack(L, 1, &ar);
//  lua_getinfo(L, "nSl", &ar);
//  int line = ar.currentline;
//
//  std::cout << "|--LUA_ERROR--| line " << line << " - " << msg << std::endl;
//}

nlohmann::json LuaScene::getPrefabData(const std::string& name)
{
  auto res = data["prefabs"][name];
  if (res == nullptr)
  {
    LOG_WARNING << "Prefab not found with name '" << name << "'";
  }
  return res;
}
