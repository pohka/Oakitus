#ifndef LUAH_RIGID_BODY_2D_H
#define LUAH_RIGID_BODY_2D_H

#include <oak/components/rigid_body_2d.h>
#include <lua/lua.hpp>

namespace oak
{
  class LuaHRigidBody2D
  {
    RigidBody2D* ptr;

  public:
    LuaHRigidBody2D(RigidBody2D* rigidbody);
    ~LuaHRigidBody2D();

    static void reg(lua_State* L);
   // static int lua_new(lua_State* L);
    static int lua_delete(lua_State* L);
    static int getMass(lua_State* L);
    static int setMass(lua_State* L);
    static int getIsStatic(lua_State* L);
    static int setIsStatic(lua_State* L);
  };
}

#endif