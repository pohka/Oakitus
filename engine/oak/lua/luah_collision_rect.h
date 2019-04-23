#ifndef LUAH_COLLISION_RECT_H
#define LUAH_COLLISION_RECT_H

#include <lua/lua.hpp>
#include <oak/collision/collision_rect.h>


namespace oak
{
  //handler for CollisionRect
  class LuaHCollisionRect
  {
    CollisionRect* ptr;
  public:
    LuaHCollisionRect(CollisionRect* rect);
    ~LuaHCollisionRect();

    //register metatable
    static void reg(lua_State* L);

  private:
    //metatable functions
    static int lua_delete(lua_State* L);
    static int getW(lua_State* L);
    static int setW(lua_State* L);
    static int getH(lua_State* L);
    static int setH(lua_State* L);
    static int getOffset(lua_State* L);
    static int setOffset(lua_State* L);
    static int getType(lua_State* L);
  };
}

#endif