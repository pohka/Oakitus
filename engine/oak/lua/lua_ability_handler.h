#ifndef LUA_ABILITY_HANDLER_H
#define LUA_ABILITY_HANDLER_H

#include <oak/lua/lua_ability.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_constants.h>

namespace oak
{
  class LuaAbilityHandler
  {
    LuaAbility* ptr;

  public:
    LuaAbilityHandler(LuaAbility* ability);
    ~LuaAbilityHandler();

    void set(LuaAbility* ability);

    static void reg(lua_State* L);

    static int lua_delete(lua_State* L);
    static int getName(lua_State* L);

    //todo:
    //static int getOwner(lua_State* L);
    //static int getKV(lua_State* L);
    static int getCooldown(lua_State* L);
    //static int isCooldownReady(lua_State* L);
    //static int getCooldownTimeRemaining(lua_State* L);
    //static int hasOwnerEnoughMana(lua_State* L);
    static int getManaCost(lua_State* L);
    static int getMaxLevel(lua_State* L);
    static int getLevel(lua_State* L);
    static int levelUp(lua_State* L);

  };
}

#endif