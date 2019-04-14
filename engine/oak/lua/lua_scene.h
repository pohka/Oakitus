#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include <oak/scene/scene.h>
#include <string>
#include <nlohmann/json.hpp>
#include <oak/ecs/entity.h>
#include <vector>

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

  class LuaScene : public oak::Scene
  {
    static LuaScene* scene; //is this needed?, probably bad practice. scene manger already exposes the scene
    
    std::string path;
    nlohmann::json data;
    bool dataLoaded = false;


  public:

    LuaScene(std::string path);
    void onLoad() override;

    nlohmann::json getPrefabData(const std::string& name);

  private:


    void setPrecacheFromData();
    void validatePrefabData();
  };
}

#endif