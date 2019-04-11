#include <oak/lua/lua_collision_circle.h>
#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_constants.h>

using namespace oak;

LuaCollisionCircle::LuaCollisionCircle(CollisionCircle* circle)
{
  this->ptr = circle;
}

LuaCollisionCircle::~LuaCollisionCircle()
{

}

void LuaCollisionCircle::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_COLLISION_CIRCLE);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getRadius); lua_setfield(L, -2, "getRadius");
  lua_pushcfunction(L, setRadius); lua_setfield(L, -2, "setRadius");
  lua_pushcfunction(L, getOffset); lua_setfield(L, -2, "getOffset");
  lua_pushcfunction(L, setOffset); lua_setfield(L, -2, "setOffset");
  lua_pushcfunction(L, getType); lua_setfield(L, -2, "getType");
  lua_pop(L, 1);
}

int LuaCollisionCircle::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  return 0;
}

int LuaCollisionCircle::getRadius(lua_State* L)
{
  LuaCollisionCircle* circleH = *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  lua_pushnumber(L, circleH->ptr->getRadius());
  return 1;
}

int LuaCollisionCircle::setRadius(lua_State* L)
{
  LuaCollisionCircle* circleH = *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  float radius = (float)luaL_checknumber(L, 2);
  circleH->ptr->setRadius(radius);
  return 0;
}

int LuaCollisionCircle::getOffset(lua_State* L)
{
  LuaCollisionCircle* circleH = *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  glm::vec2 offset = circleH->ptr->offset();
  LuaVector::c_new(L, offset.x, offset.y, 0.0f);
  return 1;
}

int LuaCollisionCircle::setOffset(lua_State* L)
{
  LuaCollisionCircle* circleH = *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  glm::vec3 pos = LuaVector::toGLMVec(L, 2);
  circleH->ptr->setOffset(pos.x, pos.y);
  return 0;
}

int LuaCollisionCircle::getType(lua_State* L)
{
  LuaCollisionCircle* circleH = *reinterpret_cast<LuaCollisionCircle**>(lua_touserdata(L, 1));
  lua_pushinteger(L, circleH->ptr->getType());
  return 1;
}