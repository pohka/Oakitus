#ifndef LUAH_SCRIPT_H
#define LUAH_SCRIPT_H

#include <lua/lua.hpp>
#include <oak/lua/lua_script.h>

namespace oak
{
  class LuaHScript
  {
    LuaScript* script;

  public:
    LuaHScript(LuaScript* script);
    ~LuaHScript();

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