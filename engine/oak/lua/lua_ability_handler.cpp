#include <oak/lua/lua_ability_handler.h>
#include <oak/lua/lua_unit.h>

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
  lua_pushcfunction(L, levelUp); lua_setfield(L, -2, "levelUp");
  lua_pushcfunction(L, getLevel); lua_setfield(L, -2, "getLevel");
  lua_pushcfunction(L, getMaxLevel); lua_setfield(L, -2, "getMaxLevel");
  lua_pushcfunction(L, getDuration); lua_setfield(L, -2, "getDuration");
  lua_pushcfunction(L, getUnitOwner); lua_setfield(L, -2, "getUnitOwner");
  lua_pushcfunction(L, isOffCooldown); lua_setfield(L, -2, "isOffCooldown");
  lua_pushcfunction(L, getCooldownTimeRemaining); lua_setfield(L, -2, "getCooldownTimeRemaining");
  lua_pushcfunction(L, hasOwnerEnoughMana); lua_setfield(L, -2, "hasOwnerEnoughMana");
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

int LuaAbilityHandler::getMaxLevel(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushinteger(L, abilityH->ptr->getMaxLevel());
  return 1;
}

int LuaAbilityHandler::getLevel(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushinteger(L, abilityH->ptr->getLevel());
  return 1;
}

int LuaAbilityHandler::levelUp(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  abilityH->ptr->levelUp();
  return 0;
}

int LuaAbilityHandler::getDuration(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getDuration());
  return 1;
}

int LuaAbilityHandler::getUnitOwner(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  Unit* unit = abilityH->ptr->getUnitOwner();
  *reinterpret_cast<LuaUnit**>(lua_newuserdata(L, sizeof(LuaUnit*))) = new LuaUnit(unit);
  luaL_setmetatable(L, LUA_HANDLE_UNIT);
  return 1;
}

int LuaAbilityHandler::isOffCooldown(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushboolean(L, abilityH->ptr->isOffCooldown());
  return 1;
}

int LuaAbilityHandler::getCooldownTimeRemaining(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getCooldownTimeRemaining());
  return 1;
}

int LuaAbilityHandler::hasOwnerEnoughMana(lua_State* L)
{
  LuaAbilityHandler* abilityH = *reinterpret_cast<LuaAbilityHandler**>(luaL_checkudata(L, 1, LUA_HANDLE_ABILITY));
  float unitMana = abilityH->ptr->getUnitOwner()->getMana();
  float manaCost = abilityH->ptr->getManaCost();
  bool hasEnoughMana = unitMana >= manaCost;
  lua_pushboolean(L, hasEnoughMana);
  return 1;
}
