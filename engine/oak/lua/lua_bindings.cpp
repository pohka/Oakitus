#include <oak/lua/lua_bindings.h>
#include <lua/lua.hpp>

#include <oak/lua/lua_input.h>

#include <oak/lua/lua_entity.h>
#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_global.h>
#include <oak/lua/lua_sprite.h>
#include <oak/lua/lua_rigid_body_2d.h>

using namespace oak;

#define LUA_INPUT "Input"


static int emptyConstructor(lua_State* L)
{
  return 0;
}



void LuaBindings::reg(lua_State* L)
{
  LuaGlobal::reg(L);
  LuaRigidBody2D::reg(L);
  LuaVector::reg(L);
  LuaInput::reg(L);
  LuaSprite::reg(L);
  LuaEntity::reg(L);
}