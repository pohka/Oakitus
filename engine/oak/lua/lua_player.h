#ifndef LUA_PLAYER_H
#define LUA_PLAYER_H

#include <oak/player/player.h>
#include <lua/lua.hpp>

namespace oak
{
  class LuaPlayer
  {
    Player* ptr;

  public:
    LuaPlayer(Player* player);
    ~LuaPlayer();

    static void reg(lua_State* L);

  private:
    //static int lua_new(lua_State* L);
    static int lua_delete(lua_State* L);
    static int getPlayerID(lua_State* L);
  };
}

#endif