#include <oak/lua/luah_player.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/luah_entity.h>

using namespace oak;

LuaHPlayer::LuaHPlayer(Player* player)
{
  ptr = player;
}

LuaHPlayer::~LuaHPlayer()
{

}

//int LuaPlayer::lua_new(lua_State* L)
//{
//
//}

void LuaHPlayer::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_PLAYER);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getPlayerID); lua_setfield(L, -2, "getPlayerID");
  lua_pushcfunction(L, getAssignedEntity); lua_setfield(L, -2, "getAssignedEnt");
  lua_pushcfunction(L, unassignEntity); lua_setfield(L, -2, "unassignEnt");
  lua_pushcfunction(L, assignEntity); lua_setfield(L, -2, "assignEnt");
  lua_pop(L, 1);
}

int LuaHPlayer::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHPlayer**>(lua_touserdata(L, 1));
  return 0;
}

int LuaHPlayer::getPlayerID(lua_State* L)
{
  LuaHPlayer* playerH = *reinterpret_cast<LuaHPlayer**>(lua_touserdata(L, 1));
  int id = playerH->ptr->getPlayerID();
  lua_pushinteger(L, id);
  return 1;
}

int LuaHPlayer::assignEntity(lua_State* L)
{
  LuaHPlayer* playerH = *reinterpret_cast<LuaHPlayer**>(lua_touserdata(L, 1));
  LuaHEntity* entH = *reinterpret_cast<LuaHEntity**>(lua_touserdata(L, 2));
  
  playerH->ptr->assignEntity(entH->ptr);

  return 0;
}

int LuaHPlayer::unassignEntity(lua_State* L)
{
  LuaHPlayer* playerH = *reinterpret_cast<LuaHPlayer**>(lua_touserdata(L, 1));
  playerH->ptr->unassignEntity();
  return 0;
}

int LuaHPlayer::getAssignedEntity(lua_State* L)
{
  LuaHPlayer* playerH = *reinterpret_cast<LuaHPlayer**>(lua_touserdata(L, 1));
  Entity* ent = playerH->ptr->getAssignedEntity();
  if (ent != nullptr)
  {
    *reinterpret_cast<LuaHEntity**>(lua_newuserdata(L, sizeof(LuaHEntity*))) = new LuaHEntity(ent);
    luaL_setmetatable(L, LUA_HANDLER_ENTITY);
    return 1;
  }

  return 0;
}