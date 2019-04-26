#ifndef LUA_TYPES_H
#define LUA_TYPES_H

#include <lua/lua.hpp>

namespace oak
{
  //lua_Integer type conversions
  //lua_Integer is typedef for long long
  struct LuaType
  {
    static int toInt(lua_State* L, int index);
    static unsigned int toUInt(lua_State* L, int index);
    static char toChar(lua_State* L, int index);
    static unsigned char toUChar(lua_State* L, int index);
    static short toShort(lua_State* L, int index);
    static unsigned short toUShort(lua_State* L, int index);
    static float toFloat(lua_State* L, int index);
    static const char* toString(lua_State* L, int index);
  };
}

#endif