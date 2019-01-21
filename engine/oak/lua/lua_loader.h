#ifndef OAK_LUA_LOADER_H
#define OAK_LUA_LOADER_H

#include <string>

namespace oak
{
  struct LuaLoader
  {
    static void init(std::string path);
  };
}

#endif