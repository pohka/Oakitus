#include <oak/lua/luah_ability.h>
#include <oak/lua/luah_unit.h>

using namespace oak;

LuaHAbility::LuaHAbility(LuaAbility* ability) : ptr(ability)
{
}

LuaHAbility::~LuaHAbility()
{

}

void LuaHAbility::set(LuaAbility* ability)
{
  ptr = ability;
}

void LuaHAbility::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_ABILITY);
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

int LuaHAbility::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  return 0;
}

int LuaHAbility::getName(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushstring(L, abilityH->ptr->getName().c_str());
  return 1;
}

int LuaHAbility::getCooldown(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getCooldown());
  return 1;
}

int LuaHAbility::getManaCost(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getManaCost());
  return 1;
}

int LuaHAbility::getMaxLevel(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushinteger(L, abilityH->ptr->getMaxLevel());
  return 1;
}

int LuaHAbility::getLevel(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushinteger(L, abilityH->ptr->getLevel());
  return 1;
}

int LuaHAbility::levelUp(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  abilityH->ptr->levelUp();
  return 0;
}

int LuaHAbility::getDuration(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getDuration());
  return 1;
}

int LuaHAbility::getUnitOwner(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  Unit* unit = abilityH->ptr->getUnitOwner();
  *reinterpret_cast<LuaHUnit**>(lua_newuserdata(L, sizeof(LuaHUnit*))) = new LuaHUnit(unit);
  luaL_setmetatable(L, LUA_HANDLER_UNIT);
  return 1;
}

int LuaHAbility::isOffCooldown(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushboolean(L, abilityH->ptr->isOffCooldown());
  return 1;
}

int LuaHAbility::getCooldownTimeRemaining(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  lua_pushnumber(L, abilityH->ptr->getCooldownTimeRemaining());
  return 1;
}

int LuaHAbility::hasOwnerEnoughMana(lua_State* L)
{
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 1, LUA_HANDLER_ABILITY));
  float unitMana = abilityH->ptr->getUnitOwner()->getMana();
  float manaCost = abilityH->ptr->getManaCost();
  bool hasEnoughMana = unitMana >= manaCost;
  lua_pushboolean(L, hasEnoughMana);
  return 1;
}
