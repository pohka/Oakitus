#ifndef OAK_LUA_LOADER_H
#define OAK_LUA_LOADER_H

#include <string>
#include <lua/lua.hpp>
#include <map>

namespace oak
{
  struct LuaS
  {
    static void init(const std::string& path);
    static void registerBindings(lua_State* L);

    static lua_State* state;

    

    static void loadFile(const std::string& fileName);
    static void doFile(const std::string& fileName);

  private:
    static std::map<std::string, std::string> files;
  };
}

#endif