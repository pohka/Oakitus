#ifndef LUA_ENTITY_H
#define LUA_ENTITY_H

#include <lua/lua.hpp>
#include <oak/ecs/entity.h>
#include <nlohmann/json.hpp>



namespace oak
{
  class LuaEntity
  {
    const Entity* ptr;

  public :
    LuaEntity(const Entity* ent);
    ~LuaEntity();

    static void reg(lua_State* L);
    static int createByName(lua_State* L);
    static int regSelf(lua_State* L, Entity* ent);

  private:
    static void addComponent(Entity* ent, const nlohmann::json& params);

    //lua wrapper functions
    static int getName(lua_State* L);
    static int getID(lua_State* L);
    static int moveBy(lua_State* L);
    static int moveTo(lua_State* L);


    static int lua_delete(lua_State* L);


    
  };
}

#endif