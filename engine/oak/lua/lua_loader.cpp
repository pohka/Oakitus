#include "lua_loader.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <oak/lua/lua_scene.h>

using namespace oak;


void LuaLoader::init(std::string path)
{
  LuaScene* scene = new LuaScene(path + "/scripts/main.lua");
  SceneManager::loadFirstScene(scene);
}