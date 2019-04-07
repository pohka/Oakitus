#include <oak/lua/lua_global.h>
#include <string>
#include <iostream>



void LuaGlobal::reg(lua_State* L)
{
  lua_register(L, "logd", debugLog);
  lua_register(L, "log", log);
  
}

int LuaGlobal::debugLog(lua_State* L)
{
  lua_Debug ar;
  lua_getstack(L, 1, &ar);
  lua_getinfo(L, "nSl", &ar);
  int line = ar.currentline;

  const char* str = luaL_checkstring(L, 1);
  std::cout << "|--DEBUG--| " << ar.short_src << " | line " << ar.currentline << ": " << str << std::endl;

  return 0;
}

int LuaGlobal::log(lua_State* L)
{
  const char* str = luaL_checkstring(L, 1);
  std::cout << "LOG  |  " << str << std::endl;

  return 0;
}

