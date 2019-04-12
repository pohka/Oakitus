#include <oak/lua/lua_global.h>
#include <string>
#include <iostream>
#include <oak/oak_def.h>

using namespace oak;

void LuaGlobal::reg(lua_State* L)
{
  lua_register(L, "logd", debugLog);
  lua_register(L, "log", log);
  

  lua_pushinteger(L, REFLECT_SPRITE);
  lua_setglobal(L, "COMP_SPRITE");

  lua_pushinteger(L, REFLECT_RIGID_BODY_2D);
  lua_setglobal(L, "COMP_RIGIDBODY2D");

  lua_pushinteger(L, REFLECT_ANIMATOR);
  lua_setglobal(L, "COMP_ANIMATOR");

  lua_pushinteger(L, ANIM_DIRECTION_LEFT);
  lua_setglobal(L, "ANIM_DIRECTION_LEFT");

  lua_pushinteger(L, ANIM_DIRECTION_RIGHT);
  lua_setglobal(L, "ANIM_DIRECTION_RIGHT");

  lua_pushinteger(L, COLLISION_SHAPE_CIRCLE);
  lua_setglobal(L, "COLLISION_SHAPE_CIRCLE");

  lua_pushinteger(L, COLLISION_SHAPE_RECT);
  lua_setglobal(L, "COLLISION_SHAPE_RECT");
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

