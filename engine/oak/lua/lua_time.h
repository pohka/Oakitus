#pragma once
#ifndef LUA_TIME_H
#define LUA_TIME_H

#include <lua/lua.hpp>

namespace oak
{
  struct LuaTime
  {
    static int deltaTime(lua_State* L);
    static int gameTime(lua_State* L);
    static int systemTime(lua_State* L);
  };
}

#endif