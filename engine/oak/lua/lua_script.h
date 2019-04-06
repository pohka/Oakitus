#ifndef LUA_SCRIPT_H
#define LUA_SCRIPT_H

#include <oak/ecs/component.h>
#include <string>
#include <lua/lua.hpp>

namespace oak
{
  class LuaScript : public Component
  {
    std::string name;
    const static std::string PATH;
    bool errorFlagOnce = false;
    lua_State* L;
    std::string scriptFilePath;

  public:
    LuaScript(std::string name);
    ~LuaScript();

    void onTick() override;
  };
}

#endif