#ifndef LUA_ABILITY_H
#define LUA_ABILITY_H

#include <oak/ability/ability.h>
#include <lua/lua.hpp>

namespace oak
{
  class LuaAbility : public Ability
  {
    std::string scriptFilePath;

  public:
    static std::string PATH;

    LuaAbility(const std::string& name);
    ~LuaAbility();

    void onSpellCast() override;
    void onSpellStart() override;
    
  };

  //class LuaAbilityHandler
  //{
  //  Ability* ptr;

  //public:
  //  LuaAbilityHandler(Ability* ability)
  //  {
  //    ptr = ability;
  //  }
  //  ~LuaAbilityHandler()
  //  {

  //  }

  //  static void reg(lua_State* L);

  //  static int lua_delete(lua_State* L);
  //  static int getName(lua_State* L);
  //};
}

#endif