#ifndef LUA_UNIT_H
#define LUA_UNIT_H

#include <oak/components/unit.h>
#include <lua/lua.hpp>

namespace oak
{
  

  class LuaUnit
  {
    

  public:
    LuaUnit(Unit* unit);
    ~LuaUnit();

    static void reg(lua_State* L);

    Unit* unit;

  private:
    static int lua_delete(lua_State* L);
    static int getUnitName(lua_State* L);
    static int getMaxHealth(lua_State* L);
    static int getHealth(lua_State* L);
    static int getMana(lua_State* L);
    static int getMaxMana(lua_State* L);
    static int getLevel(lua_State* L);
    static int castAbility(lua_State* L);

    static int setHealth(lua_State* L);
    static int setMana(lua_State* L);
    static int heal(lua_State* L);
    static int giveMana(lua_State* L);
  };
}

#endif