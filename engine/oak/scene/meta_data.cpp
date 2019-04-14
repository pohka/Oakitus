#include <oak/scene/meta_data.h>
#include <oak/debug.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <oak/core/resources.h>
//#include <oak/scene/scene.h>

using namespace oak;

static JsonComp spriteComp("sprite", {
  JsonParam("src", MetaData::ARG_STRING),
  JsonParam("w", MetaData::ARG_UINT),
  JsonParam("h", MetaData::ARG_UINT)
  });

MetaData::MetaData()
{

}

MetaData::~MetaData()
{

}

const nlohmann::json& MetaData::getPrefabData()
{
  if (data["prefabs"] == nullptr)
  {
    LOG_WARNING << "prefabs are null";
  }
  return data["prefabs"];
  
}

void MetaData::load(Scene* scene, const char* fullPath)
{
  std::ifstream i(fullPath);
  i >> data;
  if (data != nullptr)
  {
    LOG << "loaded metadata";
    setPrecacheFromData(scene);
    LOG << "precaching metadata";
    validatePrefabData();
    LOG << "validated metadata";
    isLoaded = true;
  }
  i.close();
}

void MetaData::setPrecacheFromData(Scene* scene)
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
          scene->precache.textures.push_back(data["precache"]["textures"][i]);
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
          scene->precache.shaders.push_back(data["precache"]["shaders"][i]);
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
          scene->precache.fonts.push_back(data["precache"]["fonts"][i]);
        }
      }
    }
  }
}

void MetaData::validatePrefabData()
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


bool MetaData::validateArg(
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

bool MetaData::validateComp(const char* prefabName, const nlohmann::json& comp)
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