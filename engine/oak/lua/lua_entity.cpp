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
#include <oak/lua/lua_rigid_body_2d.h>
#include <oak/lua/lua_collision_rect.h>
#include <oak/lua/lua_collision_circle.h>
#include <oak/core/resources.h>
#include <oak/components/animator.h>
#include <oak/lua/lua_animator.h>

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
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));
  std::string name = e->ptr->getName();
  lua_pushstring(L, name.c_str());

  return 1;
}

int LuaEntity::getID(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));
  int id = e->ptr->getID();
  lua_pushinteger(L, id);

  return 1;
}

int LuaEntity::moveBy(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));

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
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));

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

void LuaEntity::set(Entity* ent)
{
  this->ptr = ent;
}

void LuaEntity::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLE_ENTITY);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getName); lua_setfield(L, -2, "getName");
  lua_pushcfunction(L, getID); lua_setfield(L, -2, "getID");
  lua_pushcfunction(L, moveBy); lua_setfield(L, -2, "moveBy");
  lua_pushcfunction(L, moveTo); lua_setfield(L, -2, "moveTo");
  lua_pushcfunction(L, getComponent); lua_setfield(L, -2, "getComponent");
  lua_pushcfunction(L, getShapeByID); lua_setfield(L, -2, "getShapeByID");
  lua_pushcfunction(L, getPosition); lua_setfield(L, -2, "getPosition");
  lua_pop(L, 1);
}


int LuaEntity::getPosition(lua_State* L)
{
  LuaEntity* e = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));
  glm::vec3 pos = e->ptr->transform->position();
  LuaVector::c_new(L, pos.x, pos.y, pos.z);
  return 1;
}


int LuaEntity::getComponent(lua_State* L)
{
  LuaEntity* entH = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));
  
  int reflectID = luaL_checkinteger(L, 2);
  char res = 1;

  switch (reflectID)
  {
    case REFLECT_SPRITE : 
    {
      Sprite* sprite = entH->ptr->getComponentWithReflection<Sprite>(reflectID);
      *reinterpret_cast<LuaSprite**>(lua_newuserdata(L, sizeof(LuaSprite*))) = new LuaSprite(sprite);
      luaL_setmetatable(L, LUA_HANDLE_SPRITE);
      break;
    }
    case REFLECT_RIGID_BODY_2D :
    {
      RigidBody2D* rb = entH->ptr->getComponentWithReflection<RigidBody2D>(reflectID);
      *reinterpret_cast<LuaRigidBody2D**>(lua_newuserdata(L, sizeof(LuaRigidBody2D*))) = new LuaRigidBody2D(rb);
      luaL_setmetatable(L, LUA_HANDLE_RIGIDBODY2D);
      break;
    }
    case REFLECT_ANIMATOR :
    {
      Animator* animator = entH->ptr->getComponentWithReflection<Animator>(reflectID);
      *reinterpret_cast<LuaAnimator**>(lua_newuserdata(L, sizeof(LuaAnimator*))) = new LuaAnimator(animator);
      luaL_setmetatable(L, LUA_HANDLE_ANIMATOR);
      break;
    }
    default:
    {
      res = 0;
    }
  }

  return res;
}

int LuaEntity::getShapeByID(lua_State* L)
{
  LuaEntity* entH = *reinterpret_cast<LuaEntity**>(luaL_checkudata(L, 1, LUA_HANDLE_ENTITY));
  int id = (int)luaL_checkinteger(L, 2);
  BaseCollisionShape* shape = entH->ptr->getCollisionShapes()[id];

  switch (shape->getType())
  {
    case COLLISION_SHAPE_RECT:
    {
      CollisionRect* rect = static_cast<CollisionRect*>(shape);
      lua_newtable(L);
      *reinterpret_cast<LuaCollisionRect**>(lua_newuserdata(L, sizeof(LuaCollisionRect*))) = new LuaCollisionRect(rect);
      luaL_setmetatable(L, LUA_HANDLE_COLLISION_RECT);
      break;
    }
    case COLLISION_SHAPE_CIRCLE:
    {
      CollisionCircle* circle = static_cast<CollisionCircle*>(shape);
      lua_newtable(L);
      *reinterpret_cast<LuaCollisionCircle**>(lua_newuserdata(L, sizeof(LuaCollisionCircle*))) = new LuaCollisionCircle(circle);
      luaL_setmetatable(L, LUA_HANDLE_COLLISION_CIRCLE);
      break;
    }

  }
  return 1;
}
