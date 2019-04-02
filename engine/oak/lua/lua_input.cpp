#include <oak/lua/lua_input.h>
#include <oak/input/input.h>

using namespace oak;

int LuaInput::isKeyDown(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 1, 0);
  char key = arg1[0];
  bool result = Input::isKeyDown(key);
  lua_pushboolean(L, result);
  
  return 1;
}

int LuaInput::isKeyUp(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 1, 0);
  char key = arg1[0];
  bool result = Input::isKeyUp(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isKeyPressed(lua_State *L)
{
  const char* arg1 = luaL_checklstring(L, 1, 0);
  char key = arg1[0];
  bool result = Input::isKeyPressed(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonDown(lua_State *L)
{
  char code = luaL_checkinteger(L, 1);
  bool result = Input::isMouseButtonDown(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonUp(lua_State *L)
{
  char code = luaL_checkinteger(L, 1);
  bool result = Input::isMouseButtonUp(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonPressed(lua_State *L)
{
  char code = luaL_checkinteger(L, 1);
  bool result = Input::isMouseButtonPressed(code);
  lua_pushboolean(L, result);

  return 1;
}