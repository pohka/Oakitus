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
#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_sprite.h>
#include <oak/lua/lua_constants.h>

#include <iostream>

using namespace oak;



LuaEntity::LuaEntity(Entity* ent)
{
  ptr = ent;
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
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITY_HANDLE));
  std::string name = e->ptr->getName();
  lua_pushstring(L, name.c_str());

  return 1;
}

int LuaEntity::getID(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITY_HANDLE));
  int id = e->ptr->getID();
  lua_pushinteger(L, id);

  return 1;
}

int LuaEntity::moveBy(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITY_HANDLE));

  float x, y, z;

  //3d 
  if (lua_gettop(L) == 4)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
    z = (float)luaL_checknumber(L, 4);
    lua_pop(L, 3);
  }
  //2d
  else if (lua_gettop(L) == 3)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
    z = 0;
  }
  else
  {
    //errror
  }


  e->ptr->transform->moveBy(x, y, z);

  return 0;
}


int LuaEntity::moveTo(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITY_HANDLE));

  float x, y, z;

  //3d 
  if (lua_gettop(L) == 4)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
    z = (float)luaL_checknumber(L, 4);
    lua_pop(L, 3);
  }
  //2d
  else if (lua_gettop(L) == 3)
  {
    x = (float)luaL_checknumber(L, 2);
    y = (float)luaL_checknumber(L, 3);
    z = 0.0f;
  }
  else
  {
    //errror
  }
  

  e->ptr->transform->moveTo(x, y, z);

  return 0;
}

void LuaEntity::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_ENTITY_HANDLE);

  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getName); lua_setfield(L, -2, "getName");
  lua_pushcfunction(L, getID); lua_setfield(L, -2, "getID");
  lua_pushcfunction(L, moveBy); lua_setfield(L, -2, "moveBy");
  lua_pushcfunction(L, moveTo); lua_setfield(L, -2, "moveTo");
  lua_pushcfunction(L, getComponent); lua_setfield(L, -2, "getComponent");
  lua_pop(L, 1);

  luaL_newmetatable(L, LUA_ENTITY);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, createByName); lua_setfield(L, -2, "create");
  lua_pushcfunction(L, findByID); lua_setfield(L, -2, "findByID");
  lua_pop(L, 1);

  lua_newtable(L);
  luaL_setmetatable(L, LUA_ENTITY);
  lua_setglobal(L, LUA_ENTITY);


  //static const uint REFLECT_NULL = 0;
  //static const uint REFLECT_TRANSFORM = 1;
  //static const uint REFLECT_ANIMATOR = 2;
  //static const uint REFLECT_RIGID_BODY_2D = 3;
  //static const uint REFLECT_SPRITE = 4;
  //static const uint REFLECT_CHUNK = 5;
  //static const uint REFLECT_LAST = 5;
  lua_pushinteger(L, REFLECT_SPRITE);
  lua_setglobal(L, "COMP_SPRITE");

  lua_pushinteger(L, REFLECT_RIGID_BODY_2D);
  lua_setglobal(L, "COMP_RIGID_BODY_2D");
}


int LuaEntity::createByName(lua_State* L)
{
  float x, y, z;

  if (lua_gettop(L) == 2)
  {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
  else if (lua_gettop(L) == 3)
  {
    glm::vec3 pos = LuaVector::toGLMVec(L, 3);
    x = pos.x;
    y = pos.y;
    z = pos.z;
  }
  else
  {
    //error
    std::cout << "error params" << std::endl;
    return 0;
  }

  const std::string name = lua_tostring(L, 2);

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
  ent->create(x, y, z);

  *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
  luaL_setmetatable(L, LUA_ENTITY_HANDLE);

  return 1;
}

int LuaEntity::regSelf(lua_State* L, Entity* ent)
{
  lua_newtable(L);
  *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
  luaL_setmetatable(L, LUA_ENTITY_HANDLE);

  lua_setglobal(L, "entity");
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

int LuaEntity::getComponent(lua_State* L)
{
  LuaEntity* entH = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_ENTITY_HANDLE));
  
  int reflectID = luaL_checkinteger(L, 2);

  switch (reflectID)
  {
    case REFLECT_SPRITE : 
      Sprite* sprite = entH->ptr->getComponentWithReflection<Sprite>(reflectID);
      *reinterpret_cast<LuaSprite**>(lua_newuserdata(L, sizeof(LuaSprite*))) = new LuaSprite(sprite);
      luaL_setmetatable(L, "Sprite");
      return 1;
      break;
  }

  return 0;
}

int LuaEntity::findByID(lua_State* L)
{
  int id = luaL_checkinteger(L, 2);
  Entity* ent = EntityManager::findEntityByID(id);

  if (ent != nullptr)
  {
    *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
    luaL_setmetatable(L, LUA_ENTITY_HANDLE);

    return 1;
  }
  //error not found

  return 0;
}