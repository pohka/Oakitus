#include "lua_scene.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale>
#include <oak/lua/lua_script.h>
#include <oak/lua/lua_s.h>
#include <oak/lua/lua_constants.h>

static const char ARG_NUMBER = 1;
static const char ARG_INT = 2;
static const char ARG_UINT = 3;
static const char ARG_STRING = 4;
static const char ARG_BOOLEAN = 5;


using namespace oak;
using json = nlohmann::json;

LuaScene* LuaScene::scene = nullptr;


static JsonComp spriteComp("sprite", {
  JsonParam("src", ARG_STRING),
  JsonParam("w", ARG_UINT),
  JsonParam("h", ARG_UINT)
});

static bool validateArg(
  const std::string& prefabName,
  const nlohmann::json& component,
  const char* key,
  const char argType,
  const bool isRequiredKey
)
{
  auto it = component.find(key);

  bool result = false;
  if (it != component.end())
  {
    auto val = it.value();

    switch (argType)
    {
    case ARG_NUMBER:
    {
      if (val.is_number())
      {
        result = true;
      }
      break;
    }
    case ARG_INT:
    {
      if (val.is_number_integer())
      {
        result = true;
      }
      break;
    }
    case ARG_UINT:
    {
      if (val.is_number_unsigned())
      {
        result = true;
      }
      break;
    }
    case ARG_STRING:
    {
      if (val.is_string())
      {
        result = true;
      }
      break;
    }
    case ARG_BOOLEAN:
    {
      if (val.is_boolean())
      {
        result = true;
      }
      break;
    }
    }
  }
  else
  {
    if (!isRequiredKey)
    {
      result = true;
    }
    else
    {
      LOG_WARNING << prefabName << ":" << component["class"] << " - no key value found for key '" << key << "'";
    }
  }

  if (result == false)
  {
    LOG_WARNING << prefabName << ":" << component["class"] << " - invalid type for key '" << key << "'";
  }

  return result;
}

static bool validateComp(const char* prefabName, const nlohmann::json& comp)
{
  bool res = true;
  if (comp["class"] != nullptr && comp["class"] == "sprite")
  {
    for (auto it : spriteComp.params)
    {
      bool isValid = validateArg(prefabName, comp, it.key, it.argType, it.isRequired);
      if (!isValid && res)
      {
        res = false;
      }
    }
  }
  return res;
}

LuaScene::LuaScene(std::string path) : Scene()
{
  this->path = path;
  std::ifstream i(path + "file.json");
  i >> data;
  if (data != nullptr)
  {
    dataLoaded = true;
    setPrecacheFromData();
    validatePrefabData();
  }

  LuaScene::scene = this;
}

void LuaScene::onLoad()
{
  //possibly change this in future to: scripts/main.lua
  //right now the VS root path for lua is not correct
  //therefore it cant find the scripts when using require() in lua
  //if you open the exe directly with the path: "scripts/main.lua", it will work but not in VS runtime
  std::string initScript;
#ifdef DEBUG_MODE
  initScript = "../Release/scripts/main.lua";
#else
  initScript = "scripts/main.lua";
#endif

  lua_State* L = LuaS::state;

  LuaS::loadFile(initScript);
  LuaS::doFile(initScript);
  lua_getglobal(LuaS::state, LUA_ON_LOAD);
  LuaS::call();
  lua_pop(LuaS::state, 1);
}

nlohmann::json LuaScene::getPrefabData(const std::string& name)
{
  auto res = data["prefabs"][name];
  if (res == nullptr)
  {
    LOG_WARNING << "Prefab not found with name '" << name << "'";
  }
  return res;
}

void LuaScene::setPrecacheFromData()
{
  //reading precache asset names
  if (data["precache"] != nullptr)
  {
    //textures
    if (data["precache"]["textures"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["textures"].size(); i++)
      {
        if (data["precache"]["textures"][i].is_string())
        {
          precache.textures.push_back(data["precache"]["textures"][i]);
        }
      }
    }
    //shaders
    if (data["precache"]["shaders"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["shaders"].size(); i++)
      {
        if (data["precache"]["shaders"][i].is_string())
        {
          precache.shaders.push_back(data["precache"]["shaders"][i]);
        }
      }
    }
    //fonts
    if (data["precache"]["fonts"] != nullptr)
    {
      for (unsigned int i = 0; i < data["precache"]["fonts"].size(); i++)
      {
        if (data["precache"]["fonts"][i].is_string())
        {
          precache.fonts.push_back(data["precache"]["fonts"][i]);
        }
      }
    }
  }
}

void LuaScene::validatePrefabData()
{
  if (data["prefabs"] != nullptr)
  {
    //iterate through each prefab
    for (auto it : data["prefabs"].items())
    {
      const char* prefabName = it.key().c_str();
      auto prefab = it.value();

      //iterate through each component on the current prefab
      for (auto compIt : prefab.items())
      {
        auto args = compIt.value();
        if (args.is_object())
        {
          validateComp(prefabName, args);
        }
      }
    }
  }
}



