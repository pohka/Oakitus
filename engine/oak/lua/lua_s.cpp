#include "lua_s.h"
#include <lua/lua.hpp>
#include <oak/debug.h>
#include <oak/oak.h>
#include <oak/lua/lua_scene.h>

#include <oak/lua/lua_input.h>
#include <oak/lua/lua_entity.h>
#include <oak/lua/lua_vector.h>
#include <oak/lua/lua_global.h>
#include <oak/lua/lua_sprite.h>
#include <oak/lua/lua_rigid_body_2d.h>
#include <oak/lua/lua_player.h>
#include <oak/lua/lua_player_resource.h>
#include <oak/lua/lua_collision_rect.h>
#include <oak/lua/lua_collision_circle.h>
#include <oak/lua/lua_animator.h>
#include <oak/lua/lua_game.h>

#include <string>
#include <fstream>
#include <streambuf>

using namespace oak;

lua_State* LuaS::state;
std::map<std::string, std::string> LuaS::files = {};

void LuaS::init(const std::string& path)
{
  LuaS::state = luaL_newstate();
  luaL_openlibs(LuaS::state);
  registerBindings(LuaS::state);

  LuaScene* scene = new LuaScene(path);

  SceneManager::loadFirstScene(scene);
}

void LuaS::registerBindings(lua_State* L)
{
  LuaGame::reg(L);
  LuaGlobal::reg(L);
  LuaPlayer::reg(L);
  LuaPlayerResource::reg(L);
  LuaRigidBody2D::reg(L);
  LuaVector::reg(L);
  LuaInput::reg(L);
  LuaSprite::reg(L);
  LuaEntity::reg(L);
  LuaCollisionRect::reg(L);
  LuaCollisionCircle::reg(L);
  LuaAnimator::reg(L);
}

void LuaS::loadFile(const std::string& fileName)
{
  //dont load file more than once
  if (files.find(fileName) == files.end())
  {
    std::ifstream ifs(fileName);
    std::string fileContent((std::istreambuf_iterator<char>(ifs)),
      std::istreambuf_iterator<char>());
    LuaS::files.insert_or_assign(fileName, fileContent);
  }
}

void LuaS::doFile(const std::string& fileName)
{
  auto it = files.find(fileName);
  if (it != files.end())
  {
    const std::string& content = it->second;
    luaL_dostring(state, content.c_str());
  }
  else
  {
    //error msg
    luaL_dostring(state, "");
  }
}