#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include <oak/scene/scene.h>
#include <lua/lua.hpp>
#include <string>

namespace oak
{
  class LuaScene : public oak::Scene
  {
    static LuaScene* scene;

  public:
    LuaScene(std::string path);
    void onLoad() override;

    static int lua_precache(lua_State *L);
  };
}

#endif