#pragma once
#ifndef LUA_GAME_H
#define LUA_GAME_H

#include <lua/lua.hpp>
#include <nlohmann/json.hpp>
#include <oak/ecs/entity.h>

namespace oak
{
  //gamemode related functions
  struct LuaGame
  {
    //register metatable
    static void reg(lua_State* L);

    //metatable functions
    //-------------------------------
    //creates an entity in the scene
    static int createEnt(lua_State* L);
    //find an entity in the scene by id
    static int findEntByID(lua_State* L);

  private:
    //add a component to the entity using the json data
    static void addComponent(Entity* ent, const nlohmann::json& params);
    //add a unit component to the entity using the json data
    static void addUnitComp(Entity* ent, const nlohmann::json& data);
  };
}

#endif