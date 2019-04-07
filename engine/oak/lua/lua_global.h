#ifndef LUA_GLOBAL_H
#define LUA_GLOBAL_H

#include <lua/lua.hpp>

namespace oak
{
  struct LuaGlobal
  {
    static void reg(lua_State* L);
    static int log(lua_State* L);
    static int debugLog(lua_State* L);
  };
}

#endif