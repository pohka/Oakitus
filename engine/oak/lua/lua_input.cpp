#include <oak/lua/lua_input.h>
#include <oak/input/input.h>
#include <oak/lua/lua_constants.h>

using namespace oak;

void LuaInput::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_INPUT);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, isKeyDown); lua_setfield(L, -2, "isKeyDown");
  lua_pushcfunction(L, isKeyUp); lua_setfield(L, -2, "isKeyUp");
  lua_pushcfunction(L, isKeyPressed); lua_setfield(L, -2, "isKeyPressed");
  lua_pushcfunction(L, isMouseButtonDown); lua_setfield(L, -2, "isMouseButtonDown");
  lua_pushcfunction(L, isMouseButtonUp); lua_setfield(L, -2, "isMouseButtonUp");
  lua_pushcfunction(L, isMouseButtonPressed); lua_setfield(L, -2, "isMouseButtonPressed");
  lua_pop(L, 1);
  luaL_setmetatable(L, LUA_INPUT);
}

int LuaInput::isKeyDown(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 2, 0);
  char key = arg1[0];
  bool result = Input::isKeyDown(key);
  lua_pushboolean(L, result);
  
  return 1;
}

int LuaInput::isKeyUp(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 2, 0);
  char key = arg1[0];
  bool result = Input::isKeyUp(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isKeyPressed(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 2, 0);
  char key = arg1[0];
  bool result = Input::isKeyPressed(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonDown(lua_State *L)
{
  char code = luaL_checkinteger(L, 2);
  bool result = Input::isMouseButtonDown(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonUp(lua_State *L)
{
  char code = luaL_checkinteger(L, 2);
  bool result = Input::isMouseButtonUp(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonPressed(lua_State *L)
{
  char code = luaL_checkinteger(L, 2);
  bool result = Input::isMouseButtonPressed(code);
  lua_pushboolean(L, result);

  return 1;
}