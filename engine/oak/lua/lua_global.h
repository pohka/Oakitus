#ifndef LUA_GLOBAL_H
#define LUA_GLOBAL_H

#include <lua/lua.hpp>

namespace oak
{
  //misc functions to expose to lua
  struct LuaGlobal
  {
    //register global functions
    static void reg(lua_State* L);

  private:
    static int log(lua_State* L);
    static int debugLog(lua_State* L);
    static int applyDamage(lua_State* L);
    static int applyHeal(lua_State* L);
  };
}

#endif