#pragma once
#ifndef LUAH_ANIMATOR_H
#define LUAH_ANIMATOR_H

#include <oak/components/animator.h>
#include <lua/lua.hpp>

namespace oak
{
  //handler for Animator component
  class LuaHAnimator
  {
    Animator* ptr;
  public:
    LuaHAnimator(Animator* animator);
    ~LuaHAnimator();

    //register metatable
    static void reg(lua_State* L);

  private:
    //metatable functions
    //-------------------------
    static int lua_delete(lua_State* L);
    static int setAnim(lua_State* L);
    static int getCurAnimID(lua_State* L);
    static int getDirection(lua_State* L);
    static int setDirection(lua_State* L);
  };
}

#endif