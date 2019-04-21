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
}

#endif