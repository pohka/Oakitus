#ifndef LUA_BINDINGS_H
#define LUA_BINDINGS_H

#include <lua/lua.hpp>

namespace oak
{
  struct LuaBindings
  {
    static void reg(lua_State* L);

  };
}

#endif