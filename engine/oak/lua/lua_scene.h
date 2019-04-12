#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include <oak/scene/scene.h>
#include <string>
#include <nlohmann/json.hpp>
#include <oak/ecs/entity.h>

namespace oak
{
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
  };
}

#endif