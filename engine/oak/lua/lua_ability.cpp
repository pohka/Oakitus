#include <oak/lua/lua_ability.h>
#include <oak/lua/lua_s.h>
#include <oak/components/unit.h>

using namespace oak;

std::string LuaAbility::PATH = "../Release/scripts/ability/";

LuaAbility::LuaAbility(const std::string& name) : Ability(name)
{
  scriptFilePath = LuaAbility::PATH + name + ".lua";
  LuaS::loadFile(scriptFilePath);
  LuaS::doFile(scriptFilePath);

  lua_getglobal(LuaS::state, name.c_str());
  lua_getfield(LuaS::state, -1, "onSpellCast");
}

LuaAbility::~LuaAbility()
{

}

void LuaAbility::onSpellCast()
{
  //todo: set unit metatables e.g. self and target
  bool hasFunc = LuaS::setFunc(scriptFilePath.c_str(), name.c_str(), "onSpellCast");
  if (hasFunc)
  {
    LuaS::setAbility(this);
    Entity* ent = this->owner->getOwnerEntity();
    LuaS::setEntity(ent);
    LuaS::call();
  }
}

void LuaAbility::onSpellStart()
{
  bool hasFunc = LuaS::setFunc(scriptFilePath.c_str(), name.c_str(), "onSpellStart");
  if (hasFunc)
  {
    LuaS::setAbility(this);
    Entity* ent = this->owner->getOwnerEntity();
    LuaS::setEntity(ent);
    LuaS::call();
  }
}