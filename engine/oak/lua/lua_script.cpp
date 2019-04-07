#include <oak/lua/lua_script.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_scene.h>
#include <iostream>
#include <oak/lua/lua_input.h>
#include <oak/lua/lua_bindings.h>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_entity.h>
#include <oak/debug.h>

using namespace oak;

const std::string LuaScript::PATH = "../Release/scripts/";

#define LUA_ON_TICK "onTick"
#define LUA_ON_CREATE "onCreate"
#define LUA_ON_DESTROY "onDestroy"

LuaScript::LuaScript(std::string name) : Component()
{
  this->name = name;
  L = luaL_newstate();
  luaL_openlibs(L);

  scriptFilePath = LuaScript::PATH + name + ".lua";
  luaL_dofile(L, scriptFilePath.c_str());
  LuaBindings::reg(L);
  

  lua_getglobal(L, name.c_str());
  if (!lua_isnil(L, -1) && lua_istable(L, -1))
  {
    lua_getfield(L, -1, LUA_ON_TICK);
    if (!lua_isnil(L, -1) && lua_isfunction(L, -1))
    {
      hasTickFunc = true;
    }
  }
}

void LuaScript::onCreate()
{
  if (hasFunc(L, LUA_ON_CREATE))
  {
    LuaEntity::regSelf(L, this->entity);
    lua_getglobal(L, name.c_str());
    lua_getfield(L, -1, LUA_ON_CREATE);

    if (lua_pcall(L, 0, 0, 0) != 0)
    {
      std::cout << "create function error" << std::endl;
    }
  }
}

void LuaScript::onDestroy()
{
  if (hasFunc(L, LUA_ON_DESTROY))
  {
    LuaEntity::regSelf(L, this->entity);
    lua_getglobal(L, name.c_str());
    lua_getfield(L, -1, LUA_ON_DESTROY);

    if (lua_pcall(L, 0, 0, 0) != 0)
    {
      std::cout << "no destroy function" << std::endl;
    }
  }
}

LuaScript::~LuaScript()
{
  lua_close(L);
}


bool LuaScript::hasFunc(lua_State* L, const char* funcName)
{
  lua_getglobal(L, name.c_str());
  if (!lua_isnil(L, -1) && lua_istable(L, -1))
  {
    lua_getfield(L, -1, funcName);
    if (!lua_isnil(L, -1) && lua_isfunction(L, -1))
    {
      return true;
    }
    else if (lua_isnil(L, -1))
    {
      LOG << "Lua function '" << name.c_str()  << "." << funcName << "' is nil";
    }
    else
    {
      LOG << "Lua global value '" << name.c_str() << "." << funcName << "' is not a function";
    }
  }
  else if (lua_isnil(L, -1))
  {
    LOG << "Lua table '" << funcName << "' is nil";
  }
  else
  {
    LOG << "Lua global value '" << funcName << "' is not a table";
  }

  return false;
}

void LuaScript::onTick()
{
  if (!hasTickFunc)
  {
    return;
  }

  LuaEntity::regSelf(L, this->entity);

  lua_getglobal(L, name.c_str());
  lua_getfield(L, -1, LUA_ON_TICK);

  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    if (errorFlagOnce == false)
    {
      errorFlagOnce = true;
      std::cout << "|--LUA_ERROR--| " << scriptFilePath << " - not found | " << lua_tostring(L, -1) << std::endl;
    }
  }
}


