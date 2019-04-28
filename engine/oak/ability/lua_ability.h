#pragma once
#ifndef LUA_ABILITY_H
#define LUA_ABILITY_H

#include <oak/ability/ability.h>
#include <lua/lua.hpp>

namespace oak
{
  //an Ability that uses meta data and a lua file to define the functionality
  class LuaAbility : public Ability
  {
    //path to the ability
    std::string scriptFilePath;

  public:
    static std::string PATH; //root ability directory

    LuaAbility(const std::string& name);
    ~LuaAbility();

    //events
    //----------------------
    //triggers when the spell button is pressed
    void onSpellCast() override;

    //triggers when the precast state has finished
    void onSpellStart() override;

  private:
    //loads the ability values from cached metadata
    void loadFromMetaData();
  };
}

#endif