#ifndef OAK_LUA_LOADER_H
#define OAK_LUA_LOADER_H

#include <string>
#include <lua/lua.hpp>

namespace oak
{
  struct LuaS
  {
    static void init(std::string path);
    static void registerBindings(lua_State* L);

    static lua_State* state;
  };
}

#endif