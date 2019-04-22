#include <oak/lua/lua_ability_handler.h>
using namespace oak;

LuaAbilityHandler::LuaAbilityHandler(LuaAbility* ability) : ptr(ability)
{
}

LuaAbilityHandler::~LuaAbilityHandler()
{

}

void LuaAbilityHandler::set(LuaAbility* ability)
{
  ptr = ability;
}

void LuaAbilityHandler::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_ABILITY);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getName); lua_setfield(L, -2, "getName");
  lua_pushcfunction(L, getManaCost); lua_setfield(L, -2, "getManaCost");
  lua_pushcfunction(L, getCooldown); lua_setfield(L, -2, "getCooldown");
  lua_pop(L, 1);
}

int LuaAbilityHandler::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  return 0;
}

int LuaAbilityHandler::getName(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushstring(L, abilityH->ptr->getName().c_str());
  return 1;
}

int LuaAbilityHandler::getCooldown(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getCooldown());
  return 1;
}

int LuaAbilityHandler::getManaCost(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getManaCost());
  return 1;
}