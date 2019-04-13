#include <oak/lua/lua_game.h>
#include <oak/lua/lua_constants.h>
#include <glm/glm.hpp>
#include <oak/debug.h>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_scene.h>
#include <oak/lua/lua_entity.h>
#include <oak/lua/lua_vector.h>

#include <oak/lua/lua_sprite.h>
#include <oak/lua/lua_collision_rect.h>
#include <oak/lua/lua_collision_circle.h>
#include <oak/lua/lua_rigid_body_2d.h>
#include <oak/lua/lua_script.h>
#include <oak/lua/lua_animator.h>

#include <oak/ecs/entity_manager.h>
#include <oak/core/resources.h>
#include <oak/lua/lua_s.h>


using namespace oak;

void LuaGame::reg(lua_State* L)
{
  luaL_newmetatable(L, LUA_GAME);
  lua_pushvalue(L, -1); lua_setfield(L, -2, "__index");
  lua_pushcfunction(L, createEnt); lua_setfield(L, -2, "createEnt");
  lua_pushcfunction(L, findEntByID); lua_setfield(L, -2, "findEntByID");
  lua_pop(L, 1);

  lua_newtable(L);
  luaL_setmetatable(L, LUA_GAME);
  lua_setglobal(L, LUA_GAME);
}

int LuaGame::createEnt(lua_State* L)
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
      LuaGame::addComponent(ent, entData[i]);
    }
  }
  ent->create(x, y, z);

  *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
  luaL_setmetatable(L, LUA_HANDLE_ENTITY);

  return 1;
}

void LuaGame::addComponent(Entity* ent, const nlohmann::json& params)
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
    RigidBody2D* rb = new RigidBody2D(isStatic);

    if (params.find("mass") != params.end())
    {
      rb->mass = params["mass"];
    }

    ent->addComponent(rb, true);
  }
  else if (className == "lua_script")
  {
    std::string name = params["name"];
    ent->addComponent(new LuaScript(name));
  }
  //animator
  else if (className == "animator")
  {
    auto animsData = params["anims"];
    Animator* animator = new Animator();

    for (unsigned int i = 0; i < animsData.size(); i++)
    {

      uchar animID = animsData[i]["id"];
      std::string src = animsData[i]["src"];
      uchar prioirty = animsData[i]["priority"];
      uint frameW = animsData[i]["frameW"];
      uint frameH = animsData[i]["frameH"];
      uint displayW = animsData[i]["displayW"];
      uint displayH = animsData[i]["displayH"];
      float frameDuration = animsData[i]["frameDuration"];
      uint totalFrameCount = animsData[i]["totalFrameCount"];
      uint startFrameY = animsData[i]["startFrameY"];
      bool isLooping = animsData[i]["isLooping"];

      SpriteAnimation* anim = new SpriteAnimation(
        src,
        prioirty,
        frameW,
        frameH,
        displayW,
        displayH,
        frameDuration,
        Resources::getDefaultShaderID(),
        totalFrameCount,
        startFrameY,
        isLooping
      );


      animator->addAnim(animID, anim);
    }

    uchar initialAnimID = params["initialAnimID"];
    animator->setAnim(initialAnimID);

    ent->addComponent(animator);
  }
  else
  {
    
  }
}

int LuaGame::findEntByID(lua_State* L)
{
  int id = luaL_checkinteger(L, 2);
  Entity* ent = EntityManager::findEntityByID(id);
  int res = 1;

  if (ent != nullptr)
  {
    *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = new LuaEntity(ent);
    luaL_setmetatable(L, LUA_HANDLE_ENTITY);
  }
  else
  {
    LuaS::log("no entity found with a matching id");
    res = 0;
  }

  return res;
}
