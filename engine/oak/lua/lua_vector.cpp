#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_s.h>
#include <string>
#include <sstream> 
#include <oak/lua/lua_constants.h>
#include <iostream>

using namespace oak;

void LuaVector::reg(lua_State* L)
{
  lua_register(L, LUA_VECTOR, lua_new);
  luaL_newmetatable(L, LUA_VECTOR);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, dot); lua_setfield(L, -2, "dot");
  lua_pushcfunction(L, toString); lua_setfield(L, -2, "toString");
  lua_pushcfunction(L, normalized); lua_setfield(L, -2, "normalized");
  lua_pushcfunction(L, length); lua_setfield(L, -2, "length");
  lua_pushcfunction(L, length2D); lua_setfield(L, -2, "length2D");
  lua_pushcfunction(L, cross); lua_setfield(L, -2, "cross");
  lua_pushcfunction(L, lua_add); lua_setfield(L, -2, "__add");
  lua_pushcfunction(L, lua_sub); lua_setfield(L, -2, "__sub");
  lua_pushcfunction(L, lua_mul); lua_setfield(L, -2, "__mul");
  lua_pushcfunction(L, lua_div); lua_setfield(L, -2, "__div");
  lua_pushcfunction(L, lua_unm); lua_setfield(L, -2, "__unm");
  lua_pop(L, 1);
}


void LuaVector::c_new(lua_State* L, float x, float y, float z)
{
  newTable(L, (float)x, (float)y, (float)z);
  luaL_setmetatable(L, LUA_VECTOR);
}

int LuaVector::lua_new(lua_State* L)
{
  lua_Number x, y, z;

  //set x,y,z with different number of arguments
  if (lua_gettop(L) == 1)
  {
    x = 0.0;
    y = 0.0;
    z = 0.0;
  }
  else if (lua_gettop(L) == 2)
  {
    x = luaL_checknumber(L, 1);
    y = luaL_checknumber(L, 2);
    z = 0.0;
  }
  else if (lua_gettop(L) == 3)
  {
    x = luaL_checknumber(L, 1);
    y = luaL_checknumber(L, 2);
    z = luaL_checknumber(L, 3);
  }
  else
  {
    LuaS::log("invalid number of arguments");
    return 0;
  }

  newTable(L, (float)x, (float)y, (float)z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::toString(lua_State* L)
{
  luaL_checktype(L, 1, LUA_TTABLE);

  lua_getfield(L, 1, "x");
  lua_getfield(L, 1, "y");
  lua_getfield(L, 1, "z");

  double x = luaL_checknumber(L, -3);
  double y = luaL_checknumber(L, -2);
  double z = luaL_checknumber(L, -1);
  lua_pop(L, 3);

  x = floorf(x*10.0f) * 0.1f;
  y = floorf(y*10.0f) * 0.1f;
  z = floorf(z*10.0f) * 0.1f;

  std::stringstream stream;


  stream << "(" << x << "," << y << "," << z << ")";
  std::string s = stream.str();

  lua_pushstring(L, s.c_str());
  return 1;
}

int LuaVector::dot(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  float res = glm::dot(a, b);

  lua_pushnumber(L, res);
  return 1;
}


int LuaVector::normalized(lua_State* L)
{
  glm::vec3 v = toGLMVec(L, 1);
  v = glm::normalize(v);

  newTable(L, v.x, v.y, v.z);
  luaL_setmetatable(L, LUA_VECTOR);
  return 1;
}

int LuaVector::length(lua_State* L)
{
  glm::vec3 v = toGLMVec(L, 1);
  lua_pushnumber(L, v.length());
  return 1;
}

int LuaVector::length2D(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec2 b(a.x, a.y);
  lua_pushnumber(L, b.length());
  return 1;
}

int LuaVector::cross(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  glm::vec3 c = glm::cross(a, b);

  newTable(L, c.x, c.y, c.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::lua_add(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  glm::vec3 c = a + b;

  newTable(L, c.x, c.y, c.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::lua_sub(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  glm::vec3 c = a - b;

  newTable(L, c.x, c.y, c.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::lua_mul(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  glm::vec3 c = a * b;

  newTable(L, c.x, c.y, c.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::lua_div(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  glm::vec3 b = toGLMVec(L, 2);
  glm::vec3 c = a / b;

  newTable(L, c.x, c.y, c.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}

int LuaVector::lua_unm(lua_State* L)
{
  glm::vec3 a = toGLMVec(L, 1);
  newTable(L, -a.x, -a.y, -a.z);
  luaL_setmetatable(L, LUA_VECTOR);

  return 1;
}


glm::vec3 LuaVector::toGLMVec(lua_State* L, const int index)
{
  luaL_checktype(L, index, LUA_TTABLE);

  float x, y, z;

  lua_getfield(L, index, "x");
  lua_getfield(L, index, "y");
  lua_getfield(L, index, "z");

  x = (float)luaL_checknumber(L, -3);
  y = (float)luaL_checknumber(L, -2);
  z = (float)luaL_checknumber(L, -1);

  lua_pop(L, 3);

  glm::vec3 v(x, y, z);
  return v;
}

void LuaVector::newTable(lua_State* L, float x, float y, float z)
{
  lua_newtable(L);
  lua_pushstring(L, "x");
  lua_pushnumber(L, x);
  lua_settable(L, -3);

  lua_pushstring(L, "y");
  lua_pushnumber(L, y);
  lua_settable(L, -3);

  lua_pushstring(L, "z");
  lua_pushnumber(L, z);
  lua_settable(L, -3);
}