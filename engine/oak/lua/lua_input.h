#ifndef LUA_INPUT_H
#define LUA_INPUT_H

#include <lua/lua.hpp>

namespace oak
{
  class LuaInput
  {
  public:
    static int isKeyDown(lua_State *L);
    static int isKeyUp(lua_State *L);
    static int isKeyPressed(lua_State *L);
    static int isMouseButtonDown(lua_State *L);
    static int isMouseButtonUp(lua_State *L);
    static int isMouseButtonPressed(lua_State *L);
  };
}

#endif