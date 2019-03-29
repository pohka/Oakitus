#ifndef LUA_SCENE_H
#define LUA_SCENE_H

#include <oak/scene/scene.h>
#include <lua/lua.hpp>
#include <string>
#include <nlohmann/json.hpp>

namespace oak
{
  class LuaScene : public oak::Scene
  {
    static LuaScene* scene;
    std::string path;
    nlohmann::json data;
    bool dataLoaded = false;

  public:
    LuaScene(std::string path);
    void onLoad() override;

    static int lua_create(lua_State *L);
    //static int lua_vector(lua_State *L);
    //static int lua_vector_log(lua_State *L);

    static void logError(lua_State* L, std::string msg);


  };
}

#endif