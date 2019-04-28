#pragma once
#ifndef LUA_PLAYER_RESOURCE_H
#define LUA_PLAYER_RESOURCE_H

#include <lua/lua.hpp>
//#include <oak/player/player_resource.h>

namespace oak
{
  class LuaPlayerResource
  {
  public:
    //register metatable
    static void reg(lua_State* L);

  private:
    //metatable functions
    //----------------------------
    static int getPlayerCount(lua_State* L);
    static int getPlayer(lua_State* L);
  };
}

#endif