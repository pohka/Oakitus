#include <oak/lua/lua_time.h>
#include <oak/time/time.h>

using namespace oak;

int LuaTime::deltaTime(lua_State* L)
{
  lua_pushnumber(L, Time::deltaTime());
  return 1;
}

int LuaTime::gameTime(lua_State* L)
{
  lua_pushnumber(L, Time::getGameTime());
  return 1;
}

int LuaTime::systemTime(lua_State* L)
{
  lua_pushnumber(L, Time::getSystemTime());
  return 1;
}