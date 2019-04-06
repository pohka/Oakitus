#include <oak/lua/lua_entity.h>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_scene.h>
//#include <nlohmann/json.hpp>
//#include <oak/ecs/entity.h>
#include <oak/components/sprite.h>
#include <oak/components/transform.h>
#include <oak/collision/collision_circle.h>
#include <oak/collision/collision_rect.h>
#include <oak/components/rigid_body_2d.h>
#include <oak/lua/lua_script.h>
#include <oak/ecs/entity_manager.h>

#include <iostream>

using namespace oak;

#define LUA_ENTITYH "Entity"


LuaEntity::LuaEntity(const Entity* ent) : ptr(ent)
{

}

LuaEntity::~LuaEntity()
{

}

int LuaEntity::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaEntity**>(lua_touserdata(L, 1));
  return 0;
}

int LuaEntity::getName(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITYH));
  std::string name = e->ptr->getName();
  lua_pushstring(L, name.c_str());

  return 1;
}

int LuaEntity::getID(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITYH));
  int id = e->ptr->getID();
  lua_pushnumber(L, id);

  return 1;
}


void LuaEntity::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_ENTITYH);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, getName); lua_setfield(L, -2, "getName");
  lua_pushcfunction(L, getID); lua_setfield(L, -2, "getID");
  lua_pop(L, 1);
}


int LuaEntity::createByName(lua_State* L)
{
  float x, y;

  if (lua_gettop(L) == 1)
  {
    x = 0.0f;
    y = 0.0f;
  }
  else if (lua_gettop(L) == 3)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
  }
  else
  {
    //error
    return 0;
  }

  const std::string name = lua_tostring(L, 1);
  LuaScene* scene = static_cast<LuaScene*>(SceneManager::getCurrentScene());
  nlohmann::json entData = scene->getPrefabData(name);

  Entity* ent = new Entity();
  ent->name = name;
  for (uint i = 0; i < entData.size(); i++)
  {
    if (entData[i]["class"] != nullptr)
    {
      LuaEntity::addComponent(ent, entData[i]);
    }
  }
  ent->create(x, y);

  *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
  luaL_setmetatable(L, LUA_ENTITYH);

  return 1;
}



void LuaEntity::addComponent(Entity* ent, const nlohmann::json& params)
{
  std::string className = params["class"];

  //sprite
  if (className == "sprite")
  {
    std::string src = params["src"];
    float w = params["w"];
    float h = params["h"];
    ent->addComponent(new Sprite(src, w, h));
  }
  //collision rect
  else if (className == "collision_rect")
  {
    float offsetX = params["offsetX"];
    float offsetY = params["offsetY"];
    float w = params["w"];
    float h = params["h"];
    ent->addCollision(new CollisionRect(offsetX, offsetY, w, h));
  }
  //collision circle
  else if (className == "collision_circle")
  {
    float offsetX = params["offsetX"];
    float offsetY = params["offsetY"];
    float radius = params["radius"];
    ent->addCollision(new CollisionCircle(radius, offsetX, offsetY));
  }
  //rigid body 2d
  else if (className == "rigidbody2d")
  {
    bool isStatic = params["isStatic"];
    ent->addComponent(new RigidBody2D(isStatic));
  }
  else if (className == "lua_script")
  {
    std::string name = params["name"];
    ent->addComponent(new LuaScript(name));
  }
}