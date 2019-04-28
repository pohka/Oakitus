#pragma once
#ifndef LUAH_PLAYER_H
#define LUAH_PLAYER_H

#include <oak/player/player.h>
#include <lua/lua.hpp>

namespace oak
{
  //handler for Player
  class LuaHPlayer
  {
    Player* ptr;

  public:
    LuaHPlayer(Player* player);
    ~LuaHPlayer();

    //register metatable
    static void reg(lua_State* L);

  private:
    //metatable functions
    //------------------------------
    static int lua_delete(lua_State* L);
    static int getPlayerID(lua_State* L);
    static int assignEntity(lua_State* L);
    static int unassignEntity(lua_State* L);
    static int getAssignedEntity(lua_State* L);
    
  };
}

#endif