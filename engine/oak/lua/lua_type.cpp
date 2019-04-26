#include <oak/lua/lua_type.h>
#include <limits>
#include <oak/build_def.h>

#ifdef DEBUG_MODE
  #include <oak/debug.h>
#endif

using namespace oak;

int LuaType::toInt(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    return (int)luaL_checkinteger(L, index);
  #else
    return (int)lua_tointeger(L, index);
  #endif
}
unsigned int LuaType::toUInt(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt >= 0)
    {
      return (unsigned int)luaInt;
    
    }
    LOG_WARNING << "conversion failed: long long was negative, must be greater than or equal to zero";
    return 0;
  #else
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt >= 0)
    {
      return (unsigned int)luaInt;
    }
    return 0;
  #endif
}

char LuaType::toChar(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt <= CHAR_MAX && luaInt >= CHAR_MIN)
    {
      return (char)luaInt;
    }
    LOG_WARNING << "conversion failed: long long was not in range of char";
    return 0;
  #else
    lua_Integer luaInt = lua_tointeger(L, index);
    if (luaInt <= CHAR_MAX && luaInt >= CHAR_MIN)
    {
      return (char)luaInt;
    }
    return 0;
  #endif
}

unsigned char LuaType::toUChar(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt <= UCHAR_MAX && luaInt >= 0)
    {
      return (unsigned char)luaInt;
    }
    LOG_WARNING << "conversion failed: long long was not in range of uchar";
    return 0;
  #else
    lua_Integer luaInt = lua_tointeger(L, index);
    if (luaInt <= UCHAR_MAX && luaInt >= 0)
    {
      return (unsigned char)luaInt;
    }
    return 0;
  #endif
}

short LuaType::toShort(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt <= SHRT_MAX && luaInt >= SHRT_MIN)
    {
      return (short)luaInt;
    }
    LOG_WARNING << "conversion failed: long long was not in range of short";
    return 0;
  #else
    lua_Integer luaInt = lua_tointeger(L, index);
    if (luaInt <= SHRT_MAX && luaInt >= SHRT_MIN)
    {
      return (short)luaInt;
    }
    return 0;
  #endif
}

unsigned short LuaType::toUShort(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    lua_Integer luaInt = luaL_checkinteger(L, index);
    if (luaInt <= USHRT_MAX && luaInt >= 0)
    {
      return (unsigned short)luaInt;
    }
    LOG_WARNING << "conversion failed: long long was not in range of unsigned short";
    return 0;
  #else
    lua_Integer luaInt = lua_tointeger(L, index);
    if (luaInt <= USHRT_MAX && luaInt >= 0)
    {
      return (unsigned short)luaInt;
    }
    return 0;
  #endif
}


float LuaType::toFloat(lua_State* L, int index)
{
#ifdef DEBUG_MODE
  return (float)luaL_checknumber(L, index);
#else
  return (float)luaL_tonumber(L, index);
#endif
}

const char* LuaType::toString(lua_State* L, int index)
{
  #ifdef DEBUG_MODE
    return luaL_checkstring(L, index);
  #else
    return luaL_tostring(L, index);
  #endif
}
