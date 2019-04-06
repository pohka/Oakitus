#include <oak/lua/lua_script.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_scene.h>
#include <iostream>
#include <oak/lua/lua_input.h>
#include <oak/lua/lua_bindings.h>
#include <oak/scene/scene_manager.h>


using namespace oak;

const std::string LuaScript::PATH = "../Release/scripts/";

LuaScript::LuaScript(std::string name) : Component()
{
  this->name = name;
  L = luaL_newstate();
  luaL_openlibs(L);

  scriptFilePath = LuaScript::PATH + name + ".lua";
  luaL_dofile(L, scriptFilePath.c_str());
  LuaBindings::reg(L);
}

LuaScript::~LuaScript()
{
  lua_close(L);
}


struct Vec2
{
  double x, y;

  Vec2(double x, double y)
  {
    this->x = x;
    this->y = y;
  }
};

#define LUA_VEC3 "Vec3"


//example using lua table to store x,y,z values
struct Vec3
{
  double x, y, z;

  static int foo(lua_State* L)
  {
    lua_pushstring(L, "x");
    lua_gettable(L, -2);
    if (lua_isnumber(L, -1))
    {
      std::cout << "x value:" << lua_tonumber(L, -1) << std::endl;
    }
    std::cout << "foo" << std::endl;
    return 0;
  }


  static int Vec3_new(lua_State* L)
  {
    lua_Number x, y, z;

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

    luaL_getmetatable(L, LUA_VEC3);
    lua_setmetatable(L, -2);
    lua_pushcfunction(L, Vec3::foo); lua_setfield(L, -2, "foo");

    return 1;
  }
};

//EXAMPLE: passing lua vector as param (entID, vector)
static int setEntPos(lua_State* L)
{
  luaL_checktype(L, 2, LUA_TTABLE);


  int entID = (int)lua_tonumber(L, 1);

  double x, y, z;

  lua_getfield(L, 2, "x");
  lua_getfield(L, 2, "y");
  lua_getfield(L, 2, "z");

  x = luaL_checknumber(L, -3);
  y = luaL_checknumber(L, -2);
  z = luaL_checknumber(L, -1);

  lua_pop(L, 3);

  std::cout << "moving ent " << entID << ": (" << x << "," << y << "," << z << ")" << std::endl;


  return 0;
}


//EXAMPLE: using metatable object and binding them with C methods
#define LUA_VEC2 "Vec2"

// Create & return MyObject instance to Lua
static int vec2_new(lua_State* L) {
  double x = luaL_checknumber(L, 1);
  double y = luaL_checknumber(L, 2);
  *reinterpret_cast<Vec2**>(lua_newuserdata(L, sizeof(Vec2*))) = new Vec2(x, y);
  luaL_setmetatable(L, LUA_VEC2);
  return 1;
}

// MyObject member functions in Lua
static int vec2_setX(lua_State* L) {
  Vec2* v = *reinterpret_cast<Vec2**>(luaL_checkudata(L, 1, LUA_VEC2));
  double x = luaL_checknumber(L, 2);
  //double y = luaL_checknumber(L, 2);
  v->x = x;
//  v->y = y;
  return 0;
}

static int vec2_getX(lua_State* L) {
  lua_pushnumber(L, (*reinterpret_cast<Vec2**>(luaL_checkudata(L, 1, LUA_VEC2)))->x);
  return 1;
}

// Free MyObject instance by Lua garbage collection
static int vec2_delete(lua_State* L) {
  delete *reinterpret_cast<Vec2**>(lua_touserdata(L, 1));
  return 0;
}

// Register Vec2 to Lua
static void register_vec2(lua_State* L) {
  lua_register(L, LUA_VEC2, vec2_new);
  luaL_newmetatable(L, LUA_VEC2);
  lua_pushcfunction(L, vec2_delete); lua_setfield(L, -2, "__gc");
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, vec2_setX); lua_setfield(L, -2, "setX");
  lua_pushcfunction(L, vec2_getX); lua_setfield(L, -2, "getX");
  lua_pop(L, 1);
}

struct LuaScriptClass
{
  LuaScriptClass() {}
  ~LuaScriptClass() {}
};

static int setClass(lua_State* L)
{
  
  return 1;
}


void LuaScript::onTick()
{
  //LuaScene* scene = static_cast<LuaScene*>(SceneManager::getCurrentScene());
  //lua_State* L = scene->getLuaState();

 // L = luaL_newstate();
 // luaL_openlibs(L);
  //luaL_newlib(L, mylib);
  
  //std::string scriptFile = LuaScript::PATH + name + ".lua";
  

  //lua_register(L, LUA_VEC3, Vec3::Vec3_new);
  //luaL_newmetatable(L, LUA_VEC3);

  //lua_register(L, "class", setClass);

  //lua_pop(L, 1);

  

  //register_vec2(L);
  

  //lua_register(L, "create", LuaScene::lua_create);
  //lua_register(L, "setEntPos", setEntPos); //example

  //lua_pop(L, 2);
  lua_getglobal(L, name.c_str());
  lua_getfield(L, -1, "tick");  // -1 means stack top.

  /* do the call (2 arguments, 1 result) */
  //lua_pcall(L, 2, 1, 0);
    
 // lua_pop(L, 1);  /* pop returned value */
  //lua_call(L, 0, 0);

  //return;

  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    if (errorFlagOnce == false)
    {
      errorFlagOnce = true;
      std::cout << "|--LUA_ERROR--| " << scriptFilePath << " - not found | " << lua_tostring(L, -1) << std::endl;
    }
  }
  //lua_pop(L, 1);
  

  //lua_close(L);
}