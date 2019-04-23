#include <oak/ability/lua_ability.h>
#include <oak/lua/lua_s.h>
#include <oak/components/unit.h>
#include <oak/meta/meta_data.h>

using namespace oak;

std::string LuaAbility::PATH = "scripts/ability/";

LuaAbility::LuaAbility(const std::string& name) : Ability(name)
{
  loadFromMetaData();

  scriptFilePath = LuaAbility::PATH + name + ".lua";
  LuaS::loadFile(scriptFilePath);
 // LuaS::doFile(scriptFilePath);

  //lua_getglobal(LuaS::state, name.c_str());
  //lua_getfield(LuaS::state, -1, "onSpellCast");
}

LuaAbility::~LuaAbility()
{

}

void LuaAbility::onSpellCast()
{
  bool hasFunc = LuaS::setFunc(scriptFilePath.c_str(), name.c_str(), "onSpellCast");
  if (hasFunc)
  {
    LuaS::setThisAbility(this);
    Entity* ent = this->owner->getOwnerEntity();
    LuaS::setThisEntity(ent);
    LuaS::call();
  }
}

void LuaAbility::onSpellStart()
{
  bool hasFunc = LuaS::setFunc(scriptFilePath.c_str(), name.c_str(), "onSpellStart");
  if (hasFunc)
  {
    LuaS::setThisAbility(this);
    Entity* ent = this->owner->getOwnerEntity();
    LuaS::setThisEntity(ent);
    LuaS::call();
  }
}

//loading variables from metadata
void LuaAbility::loadFromMetaData()
{
  auto data = MetaData::getData(META_DATA_KEY_ABILITYS);
  auto it = data.find(name);
  if (it != data.end())
  {
    auto abilData = it.value();

    //maxLevel
    auto abilIter = abilData.find("maxLevel");
    if (abilIter != abilData.end() && abilIter.value().is_number_unsigned())
    {
      maxLevel = abilIter.value();
    }

    //cooldown
    abilIter = abilData.find("cooldown");
    if (abilIter != abilData.end() && abilIter.value().is_string())
    {
      cooldown = MetaData::parseArrayString(abilIter.value());
    }
    if (cooldown.size() == 0)
    {
      cooldown.push_back(0.0f);
    }

    //manaCost
    abilIter = abilData.find("manaCost");
    if (abilIter != abilData.end() && abilIter.value().is_string())
    {
      auto result = MetaData::parseArrayString(abilIter.value());
      for (auto v : result)
      {
        manaCost.push_back((int)v);
      }
    }
    if (manaCost.size() == 0)
    {
      manaCost.push_back(0);
    }

    //duration
    abilIter = abilData.find("duration");
    if (abilIter != abilData.end() && abilIter.value().is_string())
    {
      duration = MetaData::parseArrayString(abilIter.value());
    }
    if (duration.size() == 0)
    {
      duration.push_back(0.0f);
    }

    //preCastTime
    abilIter = abilData.find("preCastTime");
    if (abilIter != abilData.end() && abilIter.value().is_number())
    {
      preCastTime = abilIter.value();
    }
  }
}
