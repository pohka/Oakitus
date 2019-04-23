#ifndef LUAH_ENTITY_H
#define LUAH_ENTITY_H

#include <lua/lua.hpp>
#include <oak/ecs/entity.h>

namespace oak
{
  class LuaHEntity
  {
  public :
    Entity* ptr;

    LuaHEntity(Entity* ent);
    ~LuaHEntity();

    static void reg(lua_State* L);

    void set(Entity* ent);

  private:
    //lua wrapper functions
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