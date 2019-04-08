#ifndef LUA_PLAYER_RESOURCE_H
#define LUA_PLAYER_RESOURCE_H

#include <lua/lua.hpp>
//#include <oak/player/player_resource.h>

namespace oak
{
  class LuaPlayerResource
  {
  public:
    static void reg(lua_State* L);
    static int getPlayerCount(lua_State* L);
    static int getPlayer(lua_State* L);
  };
}

#endif