#include <oak/lua/lua_player_resource.h>
#include <oak/player/player_resource.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/luah_player.h>
#include <oak/lua/lua_s.h>
#include <oak/lua/lua_type.h>

using namespace oak;

void LuaPlayerResource::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_PLAYER_RESOURCE);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, getPlayerCount); lua_setfield(L, -2, "getPlayerCount");
  lua_pushcfunction(L, getPlayer); lua_setfield(L, -2, "getPlayer");
  lua_pop(L, 1);

  lua_newtable(L);
  luaL_setmetatable(L, LUA_PLAYER_RESOURCE);
  lua_setglobal(L, LUA_PLAYER_RESOURCE);
}

int LuaPlayerResource::getPlayerCount(lua_State* L)
{
  lua_pushinteger(L, 1); //todo
  return 1;
}

int LuaPlayerResource::getPlayer(lua_State* L)
{
  int res = 1;
  int playerID = LuaType::toInt(L, 2);
  Player* player = PlayerResource::getPlayer(playerID);
  
  if (player != nullptr)
  {
    *reinterpret_cast<LuaHPlayer**>(lua_newuserdata(L, sizeof(LuaHPlayer*))) = new LuaHPlayer(player);
    luaL_setmetatable(L, LUA_HANDLER_PLAYER);
  }
  else
  {
    LuaS::log("No player with a matching id found");
    res = 0;
  }
  
  return res;
}