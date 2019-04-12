#ifndef LUA_GAME_H
#define LUA_GAME_H

#include <lua/lua.hpp>
#include <nlohmann/json.hpp>
#include <oak/ecs/entity.h>

namespace oak
{
  struct LuaGame
  {
    static void reg(lua_State* L);

    static int createEnt(lua_State* L);
    static int findEntByID(lua_State* L);

  private:
    static void addComponent(Entity* ent, const nlohmann::json& params);
  };
}

#endif