#include <oak/lua/lua_player.h>
#include <oak/lua/lua_constants.h>

using namespace oak;

LuaPlayer::LuaPlayer(Player* player)
{
  ptr = player;
}

LuaPlayer::~LuaPlayer()
{

}

//int LuaPlayer::lua_new(lua_State* L)
//{
//
//}

void LuaPlayer::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_PLAYER);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getPlayerID); lua_setfield(L, -2, "getPlayerID");
  lua_pop(L, 1);
}

int LuaPlayer::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaPlayer**>(lua_touserdata(L, 1));
  return 0;
}

int LuaPlayer::getPlayerID(lua_State* L)
{
  LuaPlayer* playerH = *reinterpret_cast<LuaPlayer**>(lua_touserdata(L, 1));
  int id = playerH->ptr->getPlayerID();
  lua_pushinteger(L, id);
  return 1;
}