#ifndef LUAH_SPRITE_H
#define LUAH_SPRITE_H

#include <lua/lua.hpp>
#include <oak/components/sprite.h>

namespace oak
{
  class LuaHSprite
  {
    Sprite* ptr;

  public:
      LuaHSprite(Sprite* sprite);
      ~LuaHSprite();

      //register metatable
      static void reg(lua_State* L);

     // static int lua_new(lua_State* L);
      static int lua_delete(lua_State* L);

      static int getSrc(lua_State* L);
      static int setSrc(lua_State* L);
  };
}

#endif