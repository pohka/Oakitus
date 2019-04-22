#ifndef SCENE_META_DATA_H
#define SCENE_META_DATA_H

#include <nlohmann/json.hpp>
#include <oak/scene/scene.h>

namespace oak
{
  //defines a parameter metadata structure
  class JsonParam
  {
  public:
    const char* key;
    const char argType;
    const bool isRequired;
    const unsigned char UDObjID;

    JsonParam(
      const char* key,
      const char argType,
      const bool isRequired = true,
      const unsigned char UDObjID = 0
    ) :
      key(key),
      argType(argType),
      isRequired(isRequired),
      UDObjID(UDObjID)
    {

    }
  };


  //defines an object metadata structure
  class JsonObj
  {
  public:
    std::vector<JsonParam> params;
    const unsigned char id;

    JsonObj(const unsigned char id, const std::vector<JsonParam>& params) :
      id(id), params(params)
    {

    }
  };


  //defines a component metadata structure
  class JsonComp
  {
  public:
    const char* name;
    std::vector<JsonParam> params;

    JsonComp(const char* name, const std::vector<JsonParam>& params) :
      name(name), params(params)
    {

    }

    bool hasKey(const char* key) const
    {
      for (auto it : params)
      {
        if (strcmp(it.key, key) == 0)
        {
          return true;
        }
      }

      return false;
    }
  };



  class PrefabValidator
  {
  public:
    static void validate();
    static bool isPrefabValidated(const std::string& name);

  private:
    static std::vector<std::string> validatedPrefabs;
    //validation functions
    //--------------------------------

    
    static void checkCompForUnusedKVs(const char* prefabName, const nlohmann::json& comp);
    static bool validateComp(const char* prefabName, const nlohmann::json& comp);
    static bool validatePrimitiveType(const nlohmann::json& val, const char type);

    static bool validateArg(
      const std::string& prefabName,
      const nlohmann::json& component,
      const JsonParam* param
    );

    static bool validateObj(
      const std::string& prefabName,
      const nlohmann::json& objData,
      const JsonObj* objType
    );


  };
}

#endif