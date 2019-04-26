#include <oak/lua/lua_input.h>
#include <oak/input/input.h>
#include <oak/lua/lua_constants.h>
#include <oak/input/key_codes.h>
#include <string>
#include <oak/lua/lua_type.h>
#include <oak/core/types.h>

#include <iostream>

using namespace oak;

static void regKey(lua_State* L, const std::string& str, const int val)
{
  lua_pushstring(L, str.c_str());
  lua_pushinteger(L, val);
  lua_settable(L, -3);
}

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

  //keycodes
  lua_newtable(L, LUA_KEYCODE);
  regKey(L, "A", KEYCODE_A);
  regKey(L, "B", KEYCODE_B);
  regKey(L, "C", KEYCODE_C);
  regKey(L, "D", KEYCODE_D);
  regKey(L, "E", KEYCODE_E);
  regKey(L, "F", KEYCODE_F);
  regKey(L, "G", KEYCODE_G);
  regKey(L, "H", KEYCODE_H);
  regKey(L, "I", KEYCODE_I);
  regKey(L, "J", KEYCODE_J);
  regKey(L, "K", KEYCODE_K);
  regKey(L, "L", KEYCODE_L);
  regKey(L, "M", KEYCODE_M);
  regKey(L, "N", KEYCODE_N);
  regKey(L, "O", KEYCODE_O);
  regKey(L, "P", KEYCODE_P);
  regKey(L, "Q", KEYCODE_Q);
  regKey(L, "R", KEYCODE_R);
  regKey(L, "S", KEYCODE_S);
  regKey(L, "T", KEYCODE_T);
  regKey(L, "U", KEYCODE_U);
  regKey(L, "V", KEYCODE_V);
  regKey(L, "W", KEYCODE_W);
  regKey(L, "X", KEYCODE_X);
  regKey(L, "Y", KEYCODE_Y);
  regKey(L, "Z", KEYCODE_Z);
  regKey(L, "SPACE", KEYCODE_SPACE);
  regKey(L, "APOSTROPHE", KEYCODE_APOSTROPHE);
  regKey(L, "MINUS", KEYCODE_MINUS);
  regKey(L, "PERIOD", KEYCODE_PERIOD);
  regKey(L, "SLASH", KEYCODE_SLASH);
  regKey(L, "NUM_0", KEYCODE_NUM_0);
  regKey(L, "NUM_1", KEYCODE_NUM_1);
  regKey(L, "NUM_2", KEYCODE_NUM_2);
  regKey(L, "NUM_3", KEYCODE_NUM_3);
  regKey(L, "NUM_4", KEYCODE_NUM_4);
  regKey(L, "NUM_5", KEYCODE_NUM_5);
  regKey(L, "NUM_6", KEYCODE_NUM_6);
  regKey(L, "NUM_7", KEYCODE_NUM_7);
  regKey(L, "NUM_8", KEYCODE_NUM_8);
  regKey(L, "NUM_9", KEYCODE_NUM_9);
  regKey(L, "SEMICOLON", KEYCODE_SEMICOLON);
  regKey(L, "EQUALS", KEYCODE_EQUALS);
  regKey(L, "LEFT_BRACKET", KEYCODE_LEFT_BRACKET);
  regKey(L, "BACKSLASH", KEYCODE_BACKSLASH);
  regKey(L, "RIGHT_BRACKET", KEYCODE_RIGHT_BRACKET);
  regKey(L, "GRAVE_ACCENT", KEYCODE_GRAVE_ACCENT);
  regKey(L, "ESCAPE", KEYCODE_ESCAPE);
  regKey(L, "ENTER", KEYCODE_ENTER);
  regKey(L, "TAB", KEYCODE_TAB);
  regKey(L, "BACKSPACE", KEYCODE_BACKSPACE);
//  regKey(L, "INSERT", KEYCODE_INSERT);
  regKey(L, "DELETE_KEY", KEYCODE_DELETE_KEY);
  regKey(L, "RIGHT", KEYCODE_RIGHT);
  regKey(L, "LEFT", KEYCODE_LEFT);
  regKey(L, "DOWN", KEYCODE_DOWN);
  regKey(L, "UP", KEYCODE_UP);
  regKey(L, "PAGE_UP", KEYCODE_PAGE_UP);
 // regKey(L, "PAGE_DOWN", KEYCODE_PAGE_DOWN);
//  regKey(L, "PAGE_DOWN", KEYCODE_PAGE_DOWN);
  regKey(L, "CAPS_LOCK", KEYCODE_CAPS_LOCK);
  regKey(L, "NUM_LOCK", KEYCODE_NUM_LOCK);
  regKey(L, "PRINT_SCREEN", KEYCODE_PRINT_SCREEN);
  regKey(L, "F1", KEYCODE_F1);
  regKey(L, "F2", KEYCODE_F2);
  regKey(L, "F3", KEYCODE_F3);
  regKey(L, "F4", KEYCODE_F4);
  regKey(L, "F5", KEYCODE_F5);
  regKey(L, "F6", KEYCODE_F6);
  regKey(L, "F7", KEYCODE_F7);
  regKey(L, "F8", KEYCODE_F8);
  regKey(L, "F9", KEYCODE_F9);
  regKey(L, "F10", KEYCODE_F10);
  regKey(L, "F11", KEYCODE_F11);
  regKey(L, "F12", KEYCODE_F12);
  regKey(L, "LEFT_SHIFT", KEYCODE_LEFT_SHIFT);
  regKey(L, "RIGHT_SHIFT", KEYCODE_RIGHT_SHIFT);
  regKey(L, "LEFT_CONTROL", KEYCODE_LEFT_CONTROL);
  regKey(L, "RIGHT_CONTROL", KEYCODE_RIGHT_CONTROL);
  regKey(L, "LEFT_ALT", KEYCODE_LEFT_ALT);
  regKey(L, "RIGHT_ALT", KEYCODE_RIGHT_ALT);
  regKey(L, "LEFT_SUPER", KEYCODE_LEFT_SUPER);
  regKey(L, "RIGHT_SUPER", KEYCODE_RIGHT_SUPER);
  lua_setglobal(L, LUA_KEYCODE);
}

static ushort getKey(lua_State* L)
{
  if (lua_isnumber(L, 2))
  {
    return LuaType::toInt(L, 2);
  }
  else
  {
    const char* arg1 = LuaType::toString(L, 2);
    return (ushort)arg1[0];
  }
}

int LuaInput::isKeyDown(lua_State *L)
{
  ushort key = getKey(L);
  bool result = Input::isKeyDown(key);
  lua_pushboolean(L, result);
  
  return 1;
}

int LuaInput::isKeyUp(lua_State *L)
{
  ushort key = getKey(L);
  bool result = Input::isKeyUp(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isKeyPressed(lua_State *L)
{
  ushort key = getKey(L);
  bool result = Input::isKeyPressed(key);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonDown(lua_State *L)
{
  char code = LuaType::toChar(L, 2);
  bool result = Input::isMouseButtonDown(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonUp(lua_State *L)
{
  char code = LuaType::toChar(L, 2);
  bool result = Input::isMouseButtonUp(code);
  lua_pushboolean(L, result);

  return 1;
}

int LuaInput::isMouseButtonPressed(lua_State *L)
{
  char code = LuaType::toChar(L, 2);
  bool result = Input::isMouseButtonPressed(code);
  lua_pushboolean(L, result);

  return 1;
}