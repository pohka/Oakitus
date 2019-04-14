#ifndef META_DATA_H
#define META_DATA_H

#include <nlohmann/json.hpp>
#include <oak/scene/scene.h>

namespace oak
{
  

  class JsonParam
  {
  public:
    const char* key;
    const char argType;
    const bool isRequired;

    JsonParam(const char* key, const char argType, const bool isRequired = true) :
      key(key), argType(argType), isRequired(isRequired)
    {

    }
  };

  class JsonComp
  {
  public:
    const char* name;
    std::vector<JsonParam> params;

    JsonComp(const char* name, const std::vector<JsonParam>& params) :
      name(name), params(params)
    {

    }
  };

  class MetaData
  {
  public:
    static const char ARG_NUMBER = 1;
    static const char ARG_INT = 2;
    static const char ARG_UINT = 3;
    static const char ARG_STRING = 4;
    static const char ARG_BOOLEAN = 5;

    MetaData();
    ~MetaData();
    void load(Scene* scene, const char* fullPath);
    const nlohmann::json& getPrefabData();

  private:
    nlohmann::json data;
    bool isLoaded = false;

    void setPrecacheFromData(Scene* scene);
    void validatePrefabData();

    static bool validateComp(const char* prefabName, const nlohmann::json& comp);

    static bool validateArg(
      const std::string& prefabName,
      const nlohmann::json& component,
      const char* key,
      const char argType,
      const bool isRequiredKey
    );

  };
}

#endif