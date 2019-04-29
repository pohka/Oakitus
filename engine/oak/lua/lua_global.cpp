#include <oak/lua/lua_global.h>
#include <string>
#include <iostream>
#include <oak/oak_def.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/lua_time.h>
#include <oak/lua/luah_lua_script.h>
#include <oak/lua/luah_unit.h>
#include <oak/lua/luah_ability.h>
#include <oak/ability/combat_tracker.h>
#include <oak/lua/lua_type.h>
#include <oak/collision/collision_shape.h>
#include <oak/components/animator.h>

using namespace oak;

void LuaGlobal::reg(lua_State* L)
{
  lua_register(L, "logd", debugLog);
  lua_register(L, "log", log);

  lua_register(L, "getDeltaTime", LuaTime::deltaTime);
  lua_register(L, "getSystemTime", LuaTime::systemTime);
  lua_register(L, "getGameTime", LuaTime::gameTime);

  //should change this use script
  lua_register(L, "setThink", LuaHLuaScript::setThink);
  

  lua_register(L, "applyDamage", applyDamage);
  lua_register(L, "applyHeal", applyHeal);

  lua_pushinteger(L, REFLECT_SPRITE);
  lua_setglobal(L, "COMP_SPRITE");

  lua_pushinteger(L, REFLECT_RIGID_BODY_2D);
  lua_setglobal(L, "COMP_RIGIDBODY2D");

  lua_pushinteger(L, REFLECT_ANIMATOR);
  lua_setglobal(L, "COMP_ANIMATOR");

  lua_pushinteger(L, REFLECT_UNIT);
  lua_setglobal(L, "COMP_UNIT");

  lua_pushinteger(L, static_cast<int>(AnimDirection::LEFT));
  lua_setglobal(L, "ANIM_DIRECTION_LEFT");

  lua_pushinteger(L, static_cast<int>(AnimDirection::RIGHT));
  lua_setglobal(L, "ANIM_DIRECTION_RIGHT");

  lua_pushinteger(L, static_cast<int>(CollisionShape::Type::CIRCLE));
  lua_setglobal(L, "COLLISION_SHAPE_CIRCLE");

  lua_pushinteger(L, static_cast<int>(CollisionShape::Type::RECT));
  lua_setglobal(L, "COLLISION_SHAPE_RECT");
}

//dlog
int LuaGlobal::debugLog(lua_State* L)
{
  lua_Debug ar;
  lua_getstack(L, 1, &ar);
  lua_getinfo(L, "nSl", &ar);
  int line = ar.currentline;

  const char* str = lua_tostring(L, 1);
  std::cout << "|--DEBUG--| " << ar.short_src << " | line " << ar.currentline << ": " << str << std::endl;

  return 0;
}

//log
int LuaGlobal::log(lua_State* L)
{
  const char* str = lua_tostring(L, 1);
  std::cout << "LOG  |  " << str << std::endl;

  return 0;
}

//log a damage instance to the combat tracker
int LuaGlobal::applyDamage(lua_State* L)
{
  LuaHUnit* victimH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  LuaHUnit* attackerH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 2, LUA_HANDLER_UNIT));
  int amount = LuaType::toInt(L, 3);
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 4, LUA_HANDLER_ABILITY));
  int elementType = LuaType::toChar(L, 5);

  CombatTracker::log(
    CombatTracker::ENTRY_TYPE_DAMAGE,
    victimH->unit,
    attackerH->unit,
    amount,
    abilityH->ptr,
    elementType
  );

  return 0;
}

//log a heal instance to the combat tracker
int LuaGlobal::applyHeal(lua_State* L)
{
  LuaHUnit* receiverH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 1, LUA_HANDLER_UNIT));
  LuaHUnit* giverH = *reinterpret_cast<LuaHUnit**>(luaL_checkudata(L, 2, LUA_HANDLER_UNIT));
  int amount = LuaType::toInt(L, 5);
  LuaHAbility* abilityH = *reinterpret_cast<LuaHAbility**>(luaL_checkudata(L, 4, LUA_HANDLER_ABILITY));
  char elementType = LuaType::LuaType::toChar(L, 5);

  CombatTracker::log(
    CombatTracker::ENTRY_TYPE_HEAL,
    receiverH->unit,
    giverH->unit,
    amount,
    abilityH->ptr,
    elementType
  );

  return 0;
}