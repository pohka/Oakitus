#ifndef LUAH_ABILITY_H
#define LUAH_ABILITY_H

#include <oak/lua/lua_ability.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_constants.h>

namespace oak
{
  class LuaHAbility
  {
    

  public:
    LuaHAbility(LuaAbility* ability);
    ~LuaHAbility();

    LuaAbility* ptr;

    void set(LuaAbility* ability);

    static void reg(lua_State* L);

    static int lua_delete(lua_State* L);
    static int getName(lua_State* L);

    //todo:
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