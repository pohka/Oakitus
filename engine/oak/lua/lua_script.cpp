#include <oak/lua/lua_script.h>
#include <lua/lua.hpp>
#include <oak/lua/lua_scene.h>
#include <iostream>
#include <oak/lua/lua_input.h>


using namespace oak;

const std::string LuaScript::PATH = "../Release/scripts/";

LuaScript::LuaScript(std::string name) : Component()
{
  this->name = name;
}

LuaScript::~LuaScript()
{

}

// Create a dummy struct which will be used for the pcall.
struct Pcall {
  std::string result;  // Will hold the result.

  static int run(lua_State *lua) {
    // Read the pointer to the Pcall struct.
    Pcall *p = static_cast<Pcall*>(lua_touserdata(lua, 1));

    // Get the global "EXAMPLE" and store it in the Pcall struct.
    lua_getglobal(lua, "EXAMPLE");
    const char *c = lua_tostring(lua, -1);
    if (c) p->result = c;

    // Done.
    // (Note there is no need to pop the stack, 
    // Lua will do that for us when we leave the function.)
    return 0;
  }
};

void example(lua_State* L)
{
  Pcall p;
  //lua_pushcfunction(lua, &Pcall::run);

  lua_register(L, "create", LuaScene::lua_create);
  lua_register(L, "isKeyDown", LuaInput::isKeyDown);
  lua_register(L, "isKeyUp", LuaInput::isKeyUp);
  lua_register(L, "isKeyPressed", LuaInput::isKeyPressed);
  lua_register(L, "isMouseButtonDown", LuaInput::isMouseButtonDown);
  lua_register(L, "isMouseButtonUp", LuaInput::isMouseButtonUp);
  lua_register(L, "isMouseButtonPressed", LuaInput::isMouseButtonPressed);

  lua_pushlightuserdata(L, &p);
  int result = lua_pcall(L, 1, 0, 0);

  if (result != LUA_OK) {
    // Handle error here (e.g., throw C++ exception).
    // Don't forget to pop error message off the Lua stack.
    std::cout << p.result << std::endl;
    
  }

  // Operation was successful. Return the result.
  
}
 

void LuaScript::onTick()
{
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);

  
  std::string scriptFile = LuaScript::PATH + name + ".lua";
  luaL_loadfile(L, scriptFile.c_str());
  
  lua_register(L, "create", LuaScene::lua_create);
  lua_register(L, "isKeyDown", LuaInput::isKeyDown);
  lua_register(L, "isKeyUp", LuaInput::isKeyUp);
  lua_register(L, "isKeyPressed", LuaInput::isKeyPressed);
  lua_register(L, "isMouseButtonDown", LuaInput::isMouseButtonDown);
  lua_register(L, "isMouseButtonUp", LuaInput::isMouseButtonUp);
  lua_register(L, "isMouseButtonPressed", LuaInput::isMouseButtonPressed);

  
  if (lua_pcall(L, 0, 0, 0) != 0)
  {
    if (errorFlagOnce == false)
    {
      errorFlagOnce = true;
      std::cout << "|--LUA_ERROR--| " << scriptFile << " - not found " << lua_tostring(L, -1) << std::endl;
    }
  }
  

  lua_close(L);
}