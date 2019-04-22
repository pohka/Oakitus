#include <oak/lua/lua_unit.h>
#include <oak/lua/lua_constants.h>
#include <oak/debug.h>

using namespace oak;

LuaUnit::LuaUnit(Unit* unit)
{
  this->unit = unit;
}

LuaUnit::~LuaUnit()
{

}

void LuaUnit::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_UNIT);
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
  lua_pushcfunction(L, heal); lua_setfield(L, -2, "heal");
  lua_pushcfunction(L, giveMana); lua_setfield(L, -2, "giveMana");
  lua_pop(L, 1);
}

int LuaUnit::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  return 0;
}

int LuaUnit::getUnitName(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushstring(L, unitH->unit->getName().c_str());
  return 1;
}

int LuaUnit::getMaxHealth(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushnumber(L, unitH->unit->getMaxHealth());
  return 1;
}

int LuaUnit::getHealth(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushnumber(L, unitH->unit->getHealth());
  return 1;
}

int LuaUnit::getMana(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushnumber(L, unitH->unit->getMana());
  return 1;
}

int LuaUnit::getMaxMana(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushnumber(L, unitH->unit->getMaxMana());
  return 1;
}

int LuaUnit::getLevel(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  lua_pushnumber(L, unitH->unit->getLevel());
  return 1;
}


int LuaUnit::castAbility(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  int abilityIndex = luaL_checkinteger(L, 2);

  if (abilityIndex >= 0 && abilityIndex < unitH->unit->getAbilityCount())
  {
    unitH->unit->castAbility(abilityIndex);
  }
  return 0;
}

int LuaUnit::setHealth(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  int hp = luaL_checkinteger(L, 2);

  unitH->unit->setHealth(hp);
  return 0;
}

int LuaUnit::setMana(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  int mana = luaL_checkinteger(L, 2);

  unitH->unit->setMana(mana);
  return 0;
}

int LuaUnit::heal(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  int amount = luaL_checkinteger(L, 2);

  unitH->unit->heal(amount);
  return 0;
}

int LuaUnit::giveMana(lua_State* L)
{
  LuaUnit* unitH = *reinterpret_cast<LuaUnit**>(luaL_checkudata(L, 1, LUA_HANDLE_UNIT));
  int amount = luaL_checkinteger(L, 2);

  unitH->unit->giveMana(amount);
  return 0;
}