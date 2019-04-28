#pragma once
#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include <oak/scene/scene.h>
#include <string>
#include <nlohmann/json.hpp>
#include <oak/ecs/entity.h>
#include <vector>
#include <oak/meta/meta_data.h>

namespace oak
{
  //lua driven scene
  class LuaScene : public oak::Scene
  {
    static LuaScene* scene; //is this needed?, probably bad practice. scene manger already exposes the scene
    
    //scene key name
    std::string name;

  public:

    LuaScene(const std::string& name);

    void onLoad() override;

    //set precache from loaded metadata
    void setPrecacheFromMetaData();

  private:
  };
}

#endif