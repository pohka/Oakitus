#pragma once
#ifndef LUAH_ENTITY_H
#define LUAH_ENTITY_H

#include <lua/lua.hpp>
#include <oak/ecs/entity.h>

namespace oak
{
  //handler for Entity
  class LuaHEntity
  {
  public :
    Entity* ptr;

    LuaHEntity(Entity* ent);
    ~LuaHEntity();

    //register metatable
    static void reg(lua_State* L);

    //set entity this handler is pointing to
    void set(Entity* ent);

  private:
    //metatable functions
    static int getName(lua_State* L);
    static int getID(lua_State* L);
    static int moveBy(lua_State* L);
    static int moveTo(lua_State* L);
    static int getPosition(lua_State* L);
    static int destroy(lua_State* L);
    static int getComponent(lua_State* L);
    static int getScript(lua_State* L);
    static int getShapeByID(lua_State* L);
    static int lua_delete(lua_State* L);
  };
}

#endif