#ifndef COLLISION_RECT_H
#define COLLISION_RECT_H

#include <lua/lua.hpp>
#include <oak/collision/collision_rect.h>


namespace oak
{
  class LuaCollisionRect
  {
    CollisionRect* ptr;
  public:
    LuaCollisionRect(CollisionRect* rect);
    ~LuaCollisionRect();

    static void reg(lua_State* L);

    static int lua_delete(lua_State* L);
    static int getW(lua_State* L);
    static int setW(lua_State* L);
    static int getH(lua_State* L);
    static int setH(lua_State* L);
    static int getOffset(lua_State* L);
    static int setOffset(lua_State* L);
  };
}

#endif