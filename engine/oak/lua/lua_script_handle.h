#ifndef LUA_SCRIPT_HANDLE_H
#define LUA_SCRIPT_HANDLE_H

#include <lua/lua.hpp>
#include <oak/lua/lua_script.h>

namespace oak
{
  class LuaScriptHandle
  {
    LuaScript* script;

  public:
    LuaScriptHandle(LuaScript* script);
    ~LuaScriptHandle();

    static void reg(lua_State* L);
    void set(LuaScript* script);

    static int setThink(lua_State* L);

  private:
    static int getKV(lua_State* L);
    static int setKV(lua_State* L);
    static int lua_delete(lua_State* L);
  };
}

#endif