#pragma once
#ifndef LUA_VECTOR_H
#define LUA_VECTOR_H

#include <glm/glm.hpp>
#include <lua/lua.hpp>

namespace oak
{
  //vector metatable
  class LuaVector
  {
  public:
    static void reg(lua_State* L);

    //converts a vector argument to glm vector
    static glm::vec3 toGLMVec(lua_State* L, const int index);

    //adds a new vector metatable
    static void c_new(lua_State* L, float x, float y, float z);


  private:
    //metatable functions
    //------------------------------
    static int lua_new(lua_State* L);
    static int toString(lua_State* L);
    static int dot(lua_State* L);
    static int normalized(lua_State* L);
    static int length(lua_State* L);
    static int length2D(lua_State* L);
    static int cross(lua_State* L);
    static int lua_add(lua_State* L);
    static int lua_sub(lua_State* L);
    static int lua_mul(lua_State* L);
    static int lua_unm(lua_State* L);
    static int lua_div(lua_State* L);

    //helper function to create x,y,z keys for vector table
    static void newTable(lua_State* L, float x, float y, float z);
  };
}

#endif