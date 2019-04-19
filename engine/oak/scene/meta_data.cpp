#include <oak/scene/meta_data.h>
#include <oak/debug.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <oak/core/resources.h>
#include <map>
//#include <oak/scene/scene.h>

using namespace oak;

//user defined object IDs
cnum UDOBJ_NULL= 0;
cnum UDOBJ_ANIMATION = 1;

//user defined objects
static std::vector<JsonObj> UDObjs = { 
    JsonObj(UDOBJ_ANIMATION, {
      JsonParam("src", MetaData::ARG_STRING),
      JsonParam("priority", MetaData::ARG_UINT),
      JsonParam("frameW", MetaData::ARG_UINT),
      JsonParam("frameH", MetaData::ARG_UINT),
      JsonParam("displayW", MetaData::ARG_UINT),
      JsonParam("displayH", MetaData::ARG_UINT),
      JsonParam("frameDuration", MetaData::ARG_NUMBER),
      JsonParam("totalFrameCount", MetaData::ARG_UINT),
      JsonParam("startFrameY", MetaData::ARG_UINT),
      JsonParam("isLooping", MetaData::ARG_BOOLEAN)
    }) 
};

//structure to metadata
static std::vector<JsonComp> COMP_METADATA_STRUCTURE = 
{
  JsonComp("sprite", {
    JsonParam("src", MetaData::ARG_STRING),
    JsonParam("w", MetaData::ARG_UINT),
    JsonParam("h", MetaData::ARG_UINT)
  }),
  JsonComp("collision_rect", {
    JsonParam("offsetX", MetaData::ARG_NUMBER),
    JsonParam("offsetY", MetaData::ARG_NUMBER),
    JsonParam("w", MetaData::ARG_UINT),
    JsonParam("h", MetaData::ARG_UINT)
  }),
  JsonComp("collision_circle", {
    JsonParam("offsetX", MetaData::ARG_NUMBER),
    JsonParam("offsetY", MetaData::ARG_NUMBER),
    JsonParam("radius", MetaData::ARG_NUMBER)
  }),
  JsonComp("rigidbody2d", {
    JsonParam("isStatic", MetaData::ARG_BOOLEAN),
    JsonParam("mass", MetaData::ARG_NUMBER, false),
  }),
  JsonComp("lua_script", {
    JsonParam("name", MetaData::ARG_STRING)
  }),
  JsonComp("animator", {
    JsonParam("initialAnimID", MetaData::ARG_UINT),
    JsonParam("anims", MetaData::ARG_ARRAY_OBJ, true, UDOBJ_ANIMATION)
  }),
  JsonComp("unit", {
    JsonParam("name", MetaData::ARG_STRING, true),
    JsonParam("health", MetaData::ARG_UINT, false),
    JsonParam("mana", MetaData::ARG_UINT, false),
    JsonParam("level", MetaData::ARG_UINT, false)
  })
};

//find meta structure by id
static const JsonComp* getMetaStructure(const std::string& name)
{
  for (unsigned int i = 0; i < COMP_METADATA_STRUCTURE.size(); i++)
  {
    if(COMP_METADATA_STRUCTURE[i].name == name)
    {
      return &COMP_METADATA_STRUCTURE[i];
    }
  }

  LOG_WARNING << "No metadata structure for found component '" << name << "'";

  return nullptr;
}

//find user defined object by id
static const JsonObj* getUDObj(const uchar id)
{
  for (unsigned int i=0; i<UDObjs.size(); i++)
  {
    if (UDObjs[i].id == id)
    {
      return &UDObjs[i];
    }
  }

  LOG_WARNING << "No UDObj found for id: '" << id << "'";

  return nullptr;
}

MetaData::MetaData()
{

}

MetaData::~MetaData()
{

}

//retrun the prefab data
nlohmann::json MetaData::getPrefabData(const std::string& name) const
{
  if (data["prefabs"] == nullptr)
  {
    LOG_WARNING << "prefabs is a nullptr";
  }
  else
  {
    auto res = data["prefabs"][name];
    if (res == nullptr)
    {
      LOG_WARNING << "Prefab not found with name '" << name << "'";
    }
    return res;
  }

  return nullptr;
  
}

//load the metadata from path
void MetaData::load(Scene* scene, const char* fullPath)
{
  std::ifstream i(fullPath);
  i >> data;
  if (data != nullptr)
  {
    setPrecacheFromData(scene);
    validatePrefabData();
    isLoaded = true;
  }
  i.close();
}

//setup precache for scene based on the current data loaded
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

//validate all prefabs metadata
void MetaData::validatePrefabData()
{
  if (data["prefabs"] != nullptr)
  {
    //iterate through each prefab
    for (auto it : data["prefabs"].items())
    {
      const char* prefabName = it.key().c_str();
      auto prefab = it.value();
      bool isPrefabValid = true;

      //iterate through each component on the current prefab
      for (auto compIt : prefab.items())
      {
        auto args = compIt.value();
        if (args.is_object())
        {
          bool isCompValid = validateComp(prefabName, args);
          if (!isCompValid)
          {
            isPrefabValid = false;
          }
        }
      }

      if (isPrefabValid)
      {
        validatedPrefabs.push_back(prefabName);
        LOG << "VALIDATED: " << prefabName;
      }
      else
      {
        LOG_WARNING << "Prefab not validated '" << prefabName << "'";
      }

      //check for unused keys
      for (auto compIt : prefab.items())
      {
        auto compKVs = compIt.value();
        if (compKVs.is_object())
        {
          checkCompForUnusedKVs(prefabName, compKVs);
        }
      }
    }
  }
}

//returns true if a prefab with matching name has been validated
bool MetaData::isPrefabValidated(const std::string& name) const
{
  for (const std::string& prefabName : validatedPrefabs)
  {
    if (prefabName == name)
    {
      return true;
    }
  }
  return false;
}

//validates a component metadata
bool MetaData::validateComp(const char* prefabName, const nlohmann::json& comp)
{
  bool res = true;

  if (comp["class"] != nullptr && comp["class"].is_string())
  {
    std::string className = comp["class"];
    const JsonComp* compMetaStructure = getMetaStructure(className.c_str());
    if (compMetaStructure != nullptr)
    {
      for (auto it : compMetaStructure->params)
      {
        bool isValid = validateArg(prefabName, comp, &it);
        if (!isValid)
        {
          res = false;
        }
      }
    }
    else
    {
      res = false;
    }
  }
  else
  {
    res = false;
  }

  return res;
}

//validates a primitive type metadata
bool MetaData::validatePrimitiveType(const nlohmann::json& val, const char type)
{
  bool result = false;
  switch (type)
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

  return result;
}

//validates an argument metadata
bool MetaData::validateArg(
  const std::string& prefabName,
  const nlohmann::json& component,
  const JsonParam* param
)
{
  auto it = component.find(param->key);

  bool result = true;
  if (it != component.end())
  {
    auto val = it.value();
    if (param->argType != ARG_ARRAY_OBJ)
    {
      result = validatePrimitiveType(val, param->argType);
    }
    else
    {
      if (val.is_array())
      {
        const JsonObj* obj = getUDObj(param->UDObjID);
        if (obj != nullptr)
        {
          for (auto i : val)
          {
            if (i.is_object())
            {
              if(!validateObj(prefabName, i, obj))
              {
                result = false;
              }
            }
            //not an object
            else
            {
              LOG_WARNING << param->key << " expected object in array at index " << i;
              result = false;
            }
          }
        }
        else
        {
          result = false;
        }
      }
    }
  }
  else
  {
    if (param->isRequired)
    {
      result = false;
      LOG_WARNING << prefabName << ":" << component["class"] << " - no key value found for key '" << param->key << "'";
    }
  }

  if (result == false)
  {
    LOG_WARNING << prefabName << ":" << component["class"] << " - invalid type for key '" << param->key << "'";
  }

  return result;
}


//validates a UDObject metadata
bool MetaData::validateObj(
  const std::string& prefabName,
  const nlohmann::json& objData,
  const JsonObj* objType
)
{
  bool isValid = true;
  for (auto param : objType->params)
  {
    auto it = objData.find(param.key);
    if (it != objData.end())
    {
      bool isArgValid = validatePrimitiveType(it.value(), param.argType);
      if (!isArgValid)
      {
        isValid = false;
        LOG_WARNING << " invalid type in UDObject: " << param.key;
      }
    }
    else
    {
      isValid = false;
      LOG_WARNING << "no key value found for UDObj '" << param.key << "'";
    }
  }
  return isValid;
}

//checks for unused keys in metadata file
void MetaData::checkCompForUnusedKVs(const char* prefabName, const nlohmann::json& compKVs)
{
  auto a = compKVs.find("class");
  if (a != compKVs.end())
  {
    std::string compClassName = a.value();
    for (auto it : compKVs.items())
    {
      if (it.key() != "class" && it.key() != "kv") //exceptions
      {
        const JsonComp* jsonComp = getMetaStructure(compClassName);
        if (jsonComp != nullptr)
        {
          bool hasKey = jsonComp->hasKey(it.key().c_str());
          if (!hasKey)
          {
            LOG_WARNING << "MetaData for prefab component " << prefabName << ":" << compClassName << " has an unused key '" << it.key() << "'";
          }
        }
      }
    }
  }
}