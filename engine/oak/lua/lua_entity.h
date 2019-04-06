#ifndef LUA_ENTITY_H
#define LUA_ENTITY_H

#include <lua/lua.hpp>
#include <oak/ecs/entity.h>
#include <nlohmann/json.hpp>



namespace oak
{
  struct LuaEntity
  {
    static void reg(lua_State* L);
    static int createByName(lua_State* L);

  private:
    static void addComponent(Entity* ent, const nlohmann::json& params);
  };
}

#endif