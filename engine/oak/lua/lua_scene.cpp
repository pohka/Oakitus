#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>

using namespace oak;

LuaScene* LuaScene::scene = nullptr;

LuaScene::LuaScene(std::string path) : Scene()
{
  LuaScene::scene = this;

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  lua_register(L, "precache", LuaScene::lua_precache);
  luaL_loadfile(L, path.c_str());
  lua_call(L, 0, 0);
  lua_close(L);
}

void LuaScene::onLoad()
{
  Entity* e = new Entity();
  e->addComponent(new Sprite("board.png", 64.0f, 64.0f));
  e->create();
}

int LuaScene::lua_precache(lua_State *L)
{
  int n = lua_gettop(L);

  std::string type = lua_tostring(L, 1);
  std::string path = lua_tostring(L, 2);

  if (type == "texture")
  {
    scene->precache.textures.push_back(path);
  }
  else if (type == "font")
  {
    scene->precache.fonts.push_back(path);
  }
  else if (type == "shader")
  {
    scene->precache.shaders.push_back(path);
  }
  else
  {
    LOG_WARNING << "lua precache type not found: '" << type << "'";
  }

  return 0;
}
