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
#include <oak/lua/lua_ability_handler.h>
#include <oak/lua/lua_game.h>
#include <oak/lua/lua_unit.h>
#include <oak/lua/lua_constants.h>

#include <string>
#include <fstream>
#include <streambuf>
#include <oak/debug.h>

using namespace oak;

lua_State* LuaS::state;
std::map<std::string, std::string> LuaS::files = {};
std::string LuaS::curLoadedFile = "";
LuaEntity* LuaS::curEntity = new LuaEntity(nullptr);
LuaScriptHandle* LuaS::curScript = new LuaScriptHandle(nullptr);
LuaAbilityHandler* LuaS::curAbility = new LuaAbilityHandler(nullptr);

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
  LuaScriptHandle::reg(L);
  LuaUnit::reg(L);
  LuaAbilityHandler::reg(L);

  //global accessor for instances
  lua_newtable(L);
  *reinterpret_cast<LuaEntity**>(lua_newuserdata(L, sizeof(LuaEntity*))) = LuaS::curEntity;
  luaL_setmetatable(L, LUA_HANDLE_ENTITY);
  lua_setglobal(L, LUA_ENTITY);

  lua_newtable(L);
  *reinterpret_cast<LuaScriptHandle**>(lua_newuserdata(L, sizeof(LuaScriptHandle*))) = LuaS::curScript;
  luaL_setmetatable(L, LUA_HANDLE_SCRIPT);
  lua_setglobal(L, LUA_SCRIPT);

  lua_newtable(L);
  *reinterpret_cast<LuaAbilityHandler**>(lua_newuserdata(L, sizeof(LuaAbilityHandler*))) = LuaS::curAbility;
  luaL_setmetatable(L, LUA_HANDLE_ABILITY);
  lua_setglobal(L, LUA_ABILITY);
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
    curLoadedFile = it->first;
  }
  else
  {
    //error msg
    luaL_dostring(state, "");
  }
}

void LuaS::call(const int result)
{
  if (lua_pcall(state, 0, result, 0) != 0)
  {
    std::string msg =  lua_tostring(state, -1);
    std::cout << "|--LUA--| " << curLoadedFile << " --| " << msg << std::endl;
  }
}

void LuaS::setEntity(Entity* entity)
{
  curEntity->set(entity);
}

void LuaS::close()
{
  lua_close(state);
}

void LuaS::log(const std::string& msg)
{
  lua_Debug ar;
  lua_getstack(state, 1, &ar);
  lua_getinfo(state, "nSl", &ar);
  int line = ar.currentline;

  std::cout << "|--LUA--| " << curLoadedFile <<  " - LINE " << line << " --| " << msg << std::endl;
}

void LuaS::setScript(LuaScript* script)
{
  curScript->set(script);
}

bool LuaS::setFunc(const char* filePath, const char* className, const char* funcName)
{
  LuaS::doFile(filePath);
  lua_getglobal(LuaS::state, className);
  if (!lua_isnil(LuaS::state, -1) && lua_istable(LuaS::state, -1))
  {
    lua_getfield(LuaS::state, -1, funcName);
    if (!lua_isnil(LuaS::state, -1) && lua_isfunction(LuaS::state, -1))
    {
      return true;
    }
  }

  return false;
}

void LuaS::setAbility(LuaAbility* ability)
{
  curAbility->set(ability);
}