#ifndef LUAH_LUA_SCRIPT_H
#define LUAH_LUA_SCRIPT_H

#include <lua/lua.hpp>
#include <oak/components/lua_script.h>

namespace oak
{
  //handler for LuaScript
  class LuaHLuaScript
  {
    LuaScript* script;

  public:
    LuaHLuaScript(LuaScript* script);
    ~LuaHLuaScript();

    //register metatable
    static void reg(lua_State* L);

    //set the script this handler is pointing to
    void set(LuaScript* script);

    static int setThink(lua_State* L);

  private:
    static int getKV(lua_State* L);
    static int setKV(lua_State* L);
    static int lua_delete(lua_State* L);
  };
}

#endif