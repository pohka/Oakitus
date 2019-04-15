#include <oak/lua/lua_script.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_scene.h>
#include <iostream>
#include <oak/lua/lua_input.h>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_entity.h>
#include <oak/debug.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/lua_s.h>

using namespace oak;

const std::string LuaScript::PATH = "../Release/scripts/";

LuaScript::LuaScript(std::string name) : Component()
{
  this->name = name;

  scriptFilePath = LuaScript::PATH + name + ".lua";
  LuaS::loadFile(scriptFilePath);
  LuaS::doFile(scriptFilePath);
  

  lua_getglobal(LuaS::state, name.c_str());
  if (!lua_isnil(LuaS::state, -1) && lua_istable(LuaS::state, -1))
  {
    lua_getfield(LuaS::state, -1, LUA_ON_TICK);
    if (!lua_isnil(LuaS::state, -1) && lua_isfunction(LuaS::state, -1))
    {
      hasTickFunc = true;
    }
  }
}

void LuaScript::onCreate()
{
  if (getFunc(LUA_ON_CREATE))
  {
    LuaS::setEntity(this->entity);
    LuaS::setScript(this);
    lua_getglobal(LuaS::state, name.c_str());
    lua_getfield(LuaS::state, -1, LUA_ON_CREATE);

    if (lua_pcall(LuaS::state, 0, 0, 0) != 0)
    {
      std::cout << "create function error" << std::endl;
    }
  }
}

void LuaScript::onDestroy()
{
  if (getFunc(LUA_ON_DESTROY))
  {
    LuaS::setEntity(this->entity);
    LuaS::setScript(this);
    lua_getglobal(LuaS::state, name.c_str());
    lua_getfield(LuaS::state, -1, LUA_ON_DESTROY);

    if (lua_pcall(LuaS::state, 0, 0, 0) != 0)
    {
      std::cout << "no destroy function" << std::endl;
    }
  }
}

LuaScript::~LuaScript()
{

}


bool LuaScript::getFunc(const char* funcName)
{
  LuaS::doFile(scriptFilePath);
  lua_getglobal(LuaS::state, name.c_str());
  if (!lua_isnil(LuaS::state, -1) && lua_istable(LuaS::state, -1))
  {
    lua_getfield(LuaS::state, -1, funcName);
    if (!lua_isnil(LuaS::state, -1) && lua_isfunction(LuaS::state, -1))
    {
      return true;
    }
    else if (lua_isnil(LuaS::state, -1))
    {
      LOG << "Lua function '" << name.c_str()  << "." << funcName << "' is nil";
    }
    else
    {
      LOG << "Lua global value '" << name.c_str() << "." << funcName << "' is not a function";
    }
  }
  else if (lua_isnil(LuaS::state, -1))
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

  LuaS::doFile(scriptFilePath);
  LuaS::setEntity(this->entity);
  LuaS::setScript(this);

  //call class::onTick()
  lua_getglobal(LuaS::state, name.c_str());
  const int top = lua_gettop(LuaS::state);
  lua_getfield(LuaS::state, -1, LUA_ON_TICK);

  LuaS::call();

  lua_settop(LuaS::state, top-1);
}


