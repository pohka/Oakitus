#ifndef LUA_ANIMATOR_H
#define LUA_ANIMATOR_H

#include <oak/components/animator.h>
#include <lua/lua.hpp>

namespace oak
{
  class LuaAnimator
  {
    Animator* ptr;
  public:
    LuaAnimator(Animator* animator);
    ~LuaAnimator();

    static void reg(lua_State* L);

  private:
    static int lua_delete(lua_State* L);
    static int setAnim(lua_State* L);
    static int getCurAnimID(lua_State* L);
    static int getDirection(lua_State* L);
    static int setDirection(lua_State* L);
  };
}

#endif