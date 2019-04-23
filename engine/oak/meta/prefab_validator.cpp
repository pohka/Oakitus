#include <oak/meta/prefab_validator.h>
#include <oak/debug.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <oak/core/resources.h>
#include <map>
#include <oak/meta/meta_data.h>

//#include <oak/scene/scene.h>

using namespace oak;

std::vector<std::string> PrefabValidator::validatedPrefabs = {};

//user defined object IDs
cnum UDOBJ_NULL= 0;
cnum UDOBJ_ANIMATION = 1;

//user defined objects
static std::vector<JsonObj> UDObjs = { 
    JsonObj(UDOBJ_ANIMATION, {
      JsonParam("src", ARG_STRING),
      JsonParam("priority", ARG_UINT),
      JsonParam("frameW", ARG_UINT),
      JsonParam("frameH", ARG_UINT),
      JsonParam("displayW", ARG_UINT),
      JsonParam("displayH", ARG_UINT),
      JsonParam("frameDuration", ARG_NUMBER),
      JsonParam("totalFrameCount", ARG_UINT),
      JsonParam("startFrameY", ARG_UINT),
      JsonParam("isLooping", ARG_BOOLEAN)
    }) 
};

//define structure of each component which will be used for comparision in validation
//structure to metadata
static std::vector<JsonComp> COMP_METADATA_STRUCTURE = 
{
  JsonComp("sprite", {
    JsonParam("src", ARG_STRING),
    JsonParam("w", ARG_UINT),
    JsonParam("h", ARG_UINT)
  }),
  JsonComp("collision_rect", {
    JsonParam("offsetX", ARG_NUMBER),
    JsonParam("offsetY", ARG_NUMBER),
    JsonParam("w", ARG_UINT),
    JsonParam("h", ARG_UINT)
  }),
  JsonComp("collision_circle", {
    JsonParam("offsetX", ARG_NUMBER),
    JsonParam("offsetY", ARG_NUMBER),
    JsonParam("radius", ARG_NUMBER)
  }),
  JsonComp("rigidbody2d", {
    JsonParam("isStatic", ARG_BOOLEAN),
    JsonParam("mass", ARG_NUMBER, false),
  }),
  JsonComp("lua_script", {
    JsonParam("name", ARG_STRING)
  }),
  JsonComp("animator", {
    JsonParam("initialAnimID", ARG_UINT),
    JsonParam("anims", ARG_ARRAY_OBJ, true, UDOBJ_ANIMATION)
  }),
  JsonComp("unit", {
    JsonParam("name", ARG_STRING, true),
    JsonParam("health", ARG_UINT, false),
    JsonParam("mana", ARG_UINT, false),
    JsonParam("level", ARG_UINT, false),
    JsonParam("ability0", ARG_STRING, false),
    JsonParam("ability1", ARG_STRING, false),
    JsonParam("ability2", ARG_STRING, false),
    JsonParam("ability3", ARG_STRING, false),
    JsonParam("ability4", ARG_STRING, false),
    JsonParam("ability5", ARG_STRING, false),
    JsonParam("ability6", ARG_STRING, false),
    JsonParam("ability7", ARG_STRING, false)
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

//validate all prefabs metadata
void PrefabValidator::validate()
{
  auto data = MetaData::getData(META_DATA_KEY_SCENE);
  auto it = data.find("prefabs");
  if (it != data.end())
  {
    //iterate through each prefab
    for (auto prefabIter : it.value().items())
    {
      const char* prefabName = prefabIter.key().c_str();
      auto prefab = prefabIter.value();
      bool isPrefabValid = true;

      //iterate through each component on the current prefab
      for (auto compIter : prefab.items())
      {
        auto args = compIter.value();
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
      for (auto compIter : prefab.items())
      {
        auto compKVs = compIter.value();
        if (compKVs.is_object())
        {
          checkCompForUnusedKVs(prefabName, compKVs);
        }
      }
    }
  }
}

//returns true if a prefab with matching name has been validated
bool PrefabValidator::isPrefabValidated(const std::string& name)
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
bool PrefabValidator::validateComp(const char* prefabName, const nlohmann::json& comp)
{
  bool res = true;

  auto it = comp.find("class");
  if (it!=comp.end() && it.value().is_string())
  {
    std::string className = it.value();
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
bool PrefabValidator::validatePrimitiveType(const nlohmann::json& val, const char type)
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
bool PrefabValidator::validateArg(
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
bool PrefabValidator::validateObj(
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
void PrefabValidator::checkCompForUnusedKVs(const char* prefabName, const nlohmann::json& compKVs)
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