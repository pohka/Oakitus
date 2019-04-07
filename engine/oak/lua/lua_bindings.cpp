#include <oak/lua/lua_bindings.h>
#include <lua/lua.hpp>

#include <oak/lua/lua_input.h>

#include <oak/lua/lua_entity.h>
#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_global.h>

using namespace oak;

#define LUA_INPUT "Input"


static int emptyConstructor(lua_State* L)
{
  return 0;
}



void LuaBindings::reg(lua_State* L)
{
  LuaGlobal::reg(L);
  LuaVector::reg(L);
  LuaInput::reg(L);
  LuaEntity::reg(L);
}