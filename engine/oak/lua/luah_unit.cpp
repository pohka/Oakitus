#include <oak/lua/luah_unit.h>
#include <oak/lua/lua_constants.h>
#include <oak/debug.h>
#include <oak/lua/lua_type.h>

using namespace oak;

LuaHUnit::LuaHUnit(Unit* unit)
{
  this->unit = unit;
}

LuaHUnit::~LuaHUnit()
{

}

void LuaHUnit::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_UNIT);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getUnitName); lua_setfield(L, -2, "getUnitName");
  lua_pushcfunction(L, getMaxHealth); lua_setfield(L, -2, "getMaxHealth");
  lua_pushcfunction(L, getHealth); lua_setfield(L, -2, "getHealth");
  lua_pushcfunction(L, getMaxMana); lua_setfield(L, -2, "getMaxMana");
  lua_pushcfunction(L, getMana); lua_setfield(L, -2, "getMana");
  lua_pushcfunction(L, getLevel); lua_setfield(L, -2, "getLevel");
  lua_pushcfunction(L, castAbility); lua_setfield(L, -2, "castAbility");
  lua_pushcfunction(L, setMana); lua_setfield(L, -2, "setMana");
  lua_pushcfunction(L, setHealth); lua_setfield(L, -2, "setHealth");
  lua_pushcfunction(L, giveMana); lua_setfield(L, -2, "giveMana");
  lua_pop(L, 1);
}

int LuaHUnit::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  return 0;
}

int LuaHUnit::getUnitName(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushstring(L, unitH->unit->getName().c_str());
  return 1;
}

int LuaHUnit::getMaxHealth(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushinteger(L, unitH->unit->getMaxHealth());
  return 1;
}

int LuaHUnit::getHealth(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushinteger(L, unitH->unit->getHealth());
  return 1;
}

int LuaHUnit::getMana(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushinteger(L, unitH->unit->getMana());
  return 1;
}

int LuaHUnit::getMaxMana(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushinteger(L, unitH->unit->getMaxMana());
  return 1;
}

int LuaHUnit::getLevel(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  lua_pushinteger(L, unitH->unit->getLevel());
  return 1;
}


int LuaHUnit::castAbility(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  unsigned int abilityIndex = LuaType::toUInt(L, 2);

  if (abilityIndex < unitH->unit->getAbilityCount())
  {
    unitH->unit->castAbility(abilityIndex);
  }
  return 0;
}

int LuaHUnit::setHealth(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  int hp = LuaType::toInt(L, 2);

  unitH->unit->setHealth(hp);
  return 0;
}

int LuaHUnit::setMana(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  int mana = LuaType::toInt(L, 2);

  unitH->unit->setMana(mana);
  return 0;
}

int LuaHUnit::giveMana(lua_State* L)
{
  LuaHUnit* unitH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  int amount = LuaType::toInt(L, 2);

  unitH->unit->giveMana(amount);
  return 0;
}