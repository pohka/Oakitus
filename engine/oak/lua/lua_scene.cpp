#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>

#include <locale>
#include <oak/lua/lua_script.h>
#include <oak/lua/lua_s.h>
#include <oak/lua/lua_constants.h>




using namespace oak;
using json = nlohmann::json;

LuaScene* LuaScene::scene = nullptr;




LuaScene::LuaScene(std::string path) : Scene()
{
  this->path = path;
  meta = MetaData();
  std::string fullPath = path + "file.json";
  meta.load(this, fullPath.c_str());
  

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


const MetaData& LuaScene::getMetaData() const
{
  return meta;
}
