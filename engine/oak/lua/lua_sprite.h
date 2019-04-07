#ifndef LUA_SPRITE_H
#define LUA_SPRITE_H

#include <lua/lua.hpp>
#include <oak/components/sprite.h>

namespace oak
{
  class LuaSprite
  {
    Sprite* ptr;

  public:
      LuaSprite(Sprite* sprite);
      ~LuaSprite();

      static void reg(lua_State* L);

     // static int lua_new(lua_State* L);
      static int lua_delete(lua_State* L);

      static int getSrc(lua_State* L);
      static int setSrc(lua_State* L);
  };
}

#endif