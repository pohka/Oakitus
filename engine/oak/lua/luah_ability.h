#pragma once
#ifndef LUAH_ABILITY_H
#define LUAH_ABILITY_H

#include <oak/ability/lua_ability.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_constants.h>

namespace oak
{
  //handler for LuaAbility
  class LuaHAbility
  {
  public:
    LuaHAbility(LuaAbility* ability);
    ~LuaHAbility();

    LuaAbility* ptr;

    //set the current ability this handler is pointing to
    void set(LuaAbility* ability);

    //register metatable
    static void reg(lua_State* L);

  private:
    //metatable functions
    //-----------------------------------
    static int lua_delete(lua_State* L);
    static int getName(lua_State* L);
    static int getUnitOwner(lua_State* L);
    //static int getKV(lua_State* L);
    static int getCooldown(lua_State* L);
    static int isOffCooldown(lua_State* L);
    static int getCooldownTimeRemaining(lua_State* L);
    static int hasOwnerEnoughMana(lua_State* L);
    static int getManaCost(lua_State* L);
    static int getMaxLevel(lua_State* L);
    static int getLevel(lua_State* L);
    static int levelUp(lua_State* L);
    static int getDuration(lua_State* L);

  };
}

#endif