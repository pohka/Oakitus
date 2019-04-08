#include <oak/lua/lua_rigid_body_2d.h>
#include <oak/lua/lua_constants.h>
#include <iostream>

using namespace oak;

LuaRigidBody2D::LuaRigidBody2D(RigidBody2D* rigidbody)
{
  ptr = rigidbody;
}

LuaRigidBody2D::~LuaRigidBody2D()
{

}

void LuaRigidBody2D::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_RIGIDBODY2D);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getMass); lua_setfield(L, -2, "getMass");
  lua_pushcfunction(L, setMass); lua_setfield(L, -2, "setMass");
  lua_pushcfunction(L, getIsStatic); lua_setfield(L, -2, "getIsStatic");
  lua_pushcfunction(L, setIsStatic); lua_setfield(L, -2, "setIsStatic");
  lua_pop(L, 1);
}

//int LuaRigidBody2D::lua_new(lua_State* L)
//{
//
//}

int LuaRigidBody2D::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaRigidBody2D**>(lua_touserdata(L, 1));
  return 0;
}

int LuaRigidBody2D::getMass(lua_State* L)
{
  LuaRigidBody2D* rb = *reinterpret_cast<LuaRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLE_RIGIDBODY2D));
  float mass = rb->ptr->mass;
  lua_pushnumber(L, mass);

  return 1;
}

int LuaRigidBody2D::setMass(lua_State* L)
{
  LuaRigidBody2D* rb = *reinterpret_cast<LuaRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLE_RIGIDBODY2D));
  float mass = (float)luaL_checknumber(L, 2);
  rb->ptr->mass = mass;

  return 0;
}


int LuaRigidBody2D::getIsStatic(lua_State* L)
{
  LuaRigidBody2D* rb = *reinterpret_cast<LuaRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLE_RIGIDBODY2D));
  lua_pushboolean(L, rb->ptr->isStatic);
  return 1;
}

int LuaRigidBody2D::setIsStatic(lua_State* L)
{
  LuaRigidBody2D* rb = *reinterpret_cast<LuaRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLE_RIGIDBODY2D));
  if (lua_isboolean(L, 2))
  {
    rb->ptr->isStatic = lua_toboolean(L, 2);
  }

  return 0;
}