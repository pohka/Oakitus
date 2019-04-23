#include <oak/lua/luah_entity.h>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_scene.h>
#include <oak/components/sprite.h>
#include <oak/components/transform.h>
#include <oak/collision/collision_circle.h>
#include <oak/collision/collision_rect.h>
#include <oak/components/rigid_body_2d.h>
#include <oak/components/lua_script.h>
#include <oak/ecs/entity_manager.h>
#include <oak/lua/lua_vector.h>
#include <oak/lua/luah_sprite.h>
#include <oak/lua/lua_constants.h>
#include <oak/lua/luah_rigid_body_2d.h>
#include <oak/lua/luah_collision_rect.h>
#include <oak/lua/luah_collision_circle.h>
#include <oak/core/resources.h>
#include <oak/components/animator.h>
#include <oak/lua/luah_animator.h>
#include <oak/components/unit.h>
#include <oak/lua/luah_unit.h>

#include <oak/lua/lua_s.h>

using namespace oak;



LuaHEntity::LuaHEntity(Entity* ent)
{
  ptr = ent;
}

LuaHEntity::~LuaHEntity()
{

}

int LuaHEntity::lua_delete(lua_State* L)
{
  delete *reinterpret_cast<LuaHEntity**>(lua_touserdata(L, 1));
  return 0;
}

int LuaHEntity::getName(lua_State* L)
{
  LuaHEntity* e = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  std::string name = e->ptr->getName();
  lua_pushstring(L, name.c_str());

  return 1;
}

int LuaHEntity::getID(lua_State* L)
{
  LuaHEntity* e = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  int id = e->ptr->getID();
  lua_pushinteger(L, id);

  return 1;
}

int LuaHEntity::moveBy(lua_State* L)
{
  LuaHEntity* e = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));

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
    LuaS::log("invalid number of arguments");
  }


  e->ptr->transform->moveBy(x, y, z);

  return 0;
}


int LuaHEntity::moveTo(lua_State* L)
{
  LuaHEntity* e = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));

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
    LuaS::log("invalid number of arguments");
  }
  

  e->ptr->transform->moveTo(x, y, z);

  return 0;
}

void LuaHEntity::set(Entity* ent)
{
  this->ptr = ent;
}

void LuaHEntity::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_HANDLER_ENTITY);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, lua_delete); lua_setfield(L, -2, "__gc");
  lua_pushcfunction(L, getName); lua_setfield(L, -2, "getName");
  lua_pushcfunction(L, getID); lua_setfield(L, -2, "getID");
  lua_pushcfunction(L, moveBy); lua_setfield(L, -2, "moveBy");
  lua_pushcfunction(L, moveTo); lua_setfield(L, -2, "moveTo");
  lua_pushcfunction(L, getComponent); lua_setfield(L, -2, "getComponent");
  lua_pushcfunction(L, getScript); lua_setfield(L, -2, "getScript");
  lua_pushcfunction(L, getShapeByID); lua_setfield(L, -2, "getShapeByID");
  lua_pushcfunction(L, getPosition); lua_setfield(L, -2, "getPosition");
  lua_pushcfunction(L, destroy); lua_setfield(L, -2, "destroy");
  lua_pop(L, 1);
}


int LuaHEntity::getPosition(lua_State* L)
{
  LuaHEntity* e = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  glm::vec3 pos = e->ptr->transform->position();
  LuaVector::c_new(L, pos.x, pos.y, pos.z);
  return 1;
}


int LuaHEntity::getComponent(lua_State* L)
{
  LuaHEntity* entH = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  
  int reflectID = luaL_checkinteger(L, 2);
  char res = 1;

  switch (reflectID)
  {
    case REFLECT_SPRITE : 
    {
      Sprite* sprite = entH->ptr->getComponentWithReflection<Sprite>(reflectID);
      if (sprite != nullptr)
      {
        *reinterpret_cast<LuaHSprite**>(lua_newuserdata(L, sizeof(LuaHSprite*))) = new LuaHSprite(sprite);
        luaL_setmetatable(L, LUA_HANDLER_SPRITE);
      }
      else
      {
        LuaS::log("No Sprite component was found in this entity");
        res = 0;
      }
      break;
    }
    case REFLECT_RIGID_BODY_2D :
    {
      RigidBody2D* rb = entH->ptr->getComponentWithReflection<RigidBody2D>(reflectID);
      if (rb != nullptr)
      {
        *reinterpret_cast<LuaHRigidBody2D**>(lua_newuserdata(L, sizeof(LuaHRigidBody2D*))) = new LuaHRigidBody2D(rb);
        luaL_setmetatable(L, LUA_HANDLER_RIGIDBODY2D);
      }
      else
      {
        LuaS::log("No Rigidbody component was found in this entity");
        res = 0;
      }
      break;
    }
    case REFLECT_ANIMATOR :
    {
      Animator* animator = entH->ptr->getComponentWithReflection<Animator>(reflectID);
      if (animator != nullptr)
      {
        *reinterpret_cast<LuaHAnimator**>(lua_newuserdata(L, sizeof(LuaHAnimator*))) = new LuaHAnimator(animator);
        luaL_setmetatable(L, LUA_HANDLER_ANIMATOR);
      }
      else
      {
        LuaS::log("No Animator component was found in this entity");
        res = 0;
      }
      break;
    }
    case REFLECT_UNIT :
    {
      Unit* unit = entH->ptr->getComponentWithReflection<Unit>(reflectID);
      if (unit != nullptr)
      {
        *reinterpret_cast<LuaHUnit**>(lua_newuserdata(L, sizeof(LuaHUnit*))) = new LuaHUnit(unit);
        luaL_setmetatable(L, LUA_HANDLER_UNIT);
      }
      else
      {
        LuaS::log("No Unit component was found in this entity");
        res = 0;
      }
      break;
    }
    default:
    {
      LuaS::log("No component found with a matching id in this entity");
      res = 0;
    }
  }

  return res;
}

int LuaHEntity::getShapeByID(lua_State* L)
{
  LuaHEntity* entH = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  int id = (int)luaL_checkinteger(L, 2);
  int res = 1;

  auto shapes = entH->ptr->getCollisionShapes();
  if (id >= shapes.size() || id < 0)
  {
    LuaS::log("No collision shapes found at id");
    res = 0;
  }
  else
  {
    BaseCollisionShape* shape = shapes[id];

    switch (shape->getType())
    {
      case COLLISION_SHAPE_RECT:
      {
        CollisionRect* rect = static_cast<CollisionRect*>(shape);
        lua_newtable(L);
        *reinterpret_cast<LuaHCollisionRect**>(lua_newuserdata(L, sizeof(LuaHCollisionRect*))) = new LuaHCollisionRect(rect);
        luaL_setmetatable(L, LUA_HANDLER_COLLISION_RECT);
        break;
      }
      case COLLISION_SHAPE_CIRCLE:
      {
        CollisionCircle* circle = static_cast<CollisionCircle*>(shape);
        lua_newtable(L);
        *reinterpret_cast<LuaHCollisionCircle**>(lua_newuserdata(L, sizeof(LuaHCollisionCircle*))) = new LuaHCollisionCircle(circle);
        luaL_setmetatable(L, LUA_HANDLER_COLLISION_CIRCLE);
        break;
      }
      default:
      {
        LuaS::log("No shape found with a matching id");
        res = 0;
      }
    }
  }
  return res;
}

int LuaHEntity::destroy(lua_State* L)
{
  LuaHEntity* entH = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));

  if (lua_gettop(L) == 2)
  {
    float delay = luaL_checknumber(L, 2);
    unsigned int entID = entH->ptr->getID();
    EntityManager::requestDestroy(entID, delay);
  }
  else
  {
    entH->ptr->destroy();
  }
  return 0;
}

//find script component with matching script name
int LuaHEntity::getScript(lua_State* L)
{
  LuaHEntity* entH = *reinterpret_cast<LuaHEntity**>(luaL_checkudata(L, 1, LUA_HANDLER_ENTITY));
  std::string scriptName = luaL_checkstring(L, 2);

  std::vector<LuaScript*> scripts = {};
  entH->ptr->getComponentsWithReflection<LuaScript>(REFLECT_LUA_SCRIPT, scripts);

  for (unsigned int i = 0; i < scripts.size(); i++)
  {
    if (scripts[i]->getName() == scriptName)
    {
      lua_newtable(L);
      *reinterpret_cast<LuaHLuaScript**>(lua_newuserdata(L, sizeof(LuaHLuaScript*))) = new LuaHLuaScript(scripts[i]);
      luaL_setmetatable(L, LUA_HANDLER_LUA_SCRIPT);
      return 1;
    }
  }

  return 0;
}