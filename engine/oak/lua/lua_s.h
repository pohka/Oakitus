#ifndef OAK_LUA_LOADER_H
#define OAK_LUA_LOADER_H

#include <string>
#include <lua/lua.hpp>
#include <map>
#include <oak/lua/lua_entity.h>
#include <oak/lua/lua_script_handle.h>

namespace oak
{
  struct LuaS
  {
    static void init(const std::string& path);
    static void registerBindings(lua_State* L);

    static lua_State* state;

    

    static void loadFile(const std::string& fileName);
    static void doFile(const std::string& fileName);
    static void call(const int result=0);
    static void setEntity(Entity* entity);
    static void close();
    static void log(const std::string& msg);
    static void setScript(LuaScript* script);


    static const LuaScriptHandle* getScriptHandle()
    {
      return curScript;
    }

  private:
    static std::map<std::string, std::string> files;
    static std::string curLoadedFile;
    static LuaEntity* curEntity;
    static LuaScriptHandle* curScript;
  };
}

#endif