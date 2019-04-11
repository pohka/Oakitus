#include <oak/lua/lua_collision_rect.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/lua_vector.h>
#include <iostream>

using namespace oak;

LuaCollisionRect::LuaCollisionRect(CollisionRect* rect)
{
  ptr = rect;
}

LuaCollisionRect::~LuaCollisionRect()
{

}

void LuaCollisionRect::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_COLLISION_RECT);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getW); lua_setfield(L, -2, "getW");
  lua_pushcfunction(L, setW); lua_setfield(L, -2, "setW");
  lua_pushcfunction(L, getH); lua_setfield(L, -2, "getH");
  lua_pushcfunction(L, setH); lua_setfield(L, -2, "setH");
  lua_pushcfunction(L, getOffset); lua_setfield(L, -2, "getOffset");
  lua_pushcfunction(L, setOffset); lua_setfield(L, -2, "setOffset");
  lua_pushcfunction(L, getType); lua_setfield(L, -2, "getType");
  lua_pop(L, 1);
}

int LuaCollisionRect::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  return 0;
}

int LuaCollisionRect::getW(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  lua_pushnumber(L, rectH->ptr->width());
  return 1;
}

int LuaCollisionRect::setW(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  float val = (float)luaL_checknumber(L, 2);
  rectH->ptr->setWidth(val);
  return 0;
}

int LuaCollisionRect::getH(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  lua_pushnumber(L, rectH->ptr->height());
  return 1;
}

int LuaCollisionRect::setH(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  float val = (float)luaL_checknumber(L, 2);
  rectH->ptr->setHeight(val);
  return 0;
}

int LuaCollisionRect::getOffset(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  glm::vec2 offset = rectH->ptr->offset();
  LuaVector::c_new(L, offset.x, offset.y, 0.0f);
  return 1;
}

int LuaCollisionRect::setOffset(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  glm::vec3 offset = LuaVector::toGLMVec(L, 2);
  rectH->ptr->setOffset(offset.x, offset.y);
  return 0;
}

int LuaCollisionRect::getType(lua_State* L)
{
  LuaCollisionRect* rectH = *reinterpret_cast<LuaCollisionRect**>(lua_touserdata(L, 1));
  lua_pushinteger(L, rectH->ptr->getType());
  return 1;
}