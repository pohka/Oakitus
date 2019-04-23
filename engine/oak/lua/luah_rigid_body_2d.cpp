#include <oak/lua/luah_rigid_body_2d.h>
#include <oak/lua/lua_constants.h>
#include <iostream>

using namespace oak;

LuaHRigidBody2D::LuaHRigidBody2D(RigidBody2D* rigidbody)
{
  ptr = rigidbody;
}

LuaHRigidBody2D::~LuaHRigidBody2D()
{

}

void LuaHRigidBody2D::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_RIGIDBODY2D);
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

int LuaHRigidBody2D::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHRigidBody2D**>(lua_touserdata(L, 1));
  return 0;
}

int LuaHRigidBody2D::getMass(lua_State* L)
{
  LuaHRigidBody2D* rb = *reinterpret_cast<LuaHRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLER_RIGIDBODY2D));
  float mass = rb->ptr->mass;
  lua_pushnumber(L, mass);

  return 1;
}

int LuaHRigidBody2D::setMass(lua_State* L)
{
  LuaHRigidBody2D* rb = *reinterpret_cast<LuaHRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLER_RIGIDBODY2D));
  float mass = (float)luaL_checknumber(L, 2);
  rb->ptr->mass = mass;

  return 0;
}


int LuaHRigidBody2D::getIsStatic(lua_State* L)
{
  LuaHRigidBody2D* rb = *reinterpret_cast<LuaHRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLER_RIGIDBODY2D));
  lua_pushboolean(L, rb->ptr->isStatic);
  return 1;
}

int LuaHRigidBody2D::setIsStatic(lua_State* L)
{
  LuaHRigidBody2D* rb = *reinterpret_cast<LuaHRigidBody2D**>(luaL_checkudata(L, 1, LUA_HANDLER_RIGIDBODY2D));
  if (lua_isboolean(L, 2))
  {
    rb->ptr->isStatic = lua_toboolean(L, 2);
  }

  return 0;
}