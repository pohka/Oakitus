#include "player.h"
#include <oak/time/time.h>
#include <oak/ecs/id_generator.h>
#include <lua/lua.hpp>
#include <oak/scene/scene_manager.h>
#include <oak/lua/lua_scene.h>
#include <oak/debug.h>

using namespace oak;

IDGenerator Player::idGen;


Player::Player()
{
  playerID = idGen.nextID();
}

Player::~Player()
{

}

uint Player::getPlayerID() const
{
  return playerID;
}

void Player::tickCommands()
{
  bool isPaused = Time::getIsPaused();
  for (Command* command : commands)
  {
    if (!isPaused || (isPaused && command->canExecuteWhenPaused))
    {
      command->onTick();
    }
  }

  std::string path = "../Release/scripts/commands/";

  for (auto str : lua_commands)
  {
    //if (!isPaused || (isPaused && command->canExecuteWhenPaused))
    //{
    //  command->onTick();
    //}
    //Scene* scene = SceneManager::getCurrentScene();
    //LuaScene* luaScene = static_cast<LuaScene*>(scene);
    //luaScene

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    std::string scriptFile = path + str + ".lua";
    luaL_loadfile(L, scriptFile.c_str());
    lua_register(L, "", LuaScene::lua_addCommand);

    if (lua_pcall(L, 0, 0, 0) != 0)
    {
      std::cout << "|--LUA_ERROR--|" << " lua_pcall - " << lua_tostring(L, -1) << std::endl;
    }
    //lua_call(L, 0, 0);
    

    lua_close(L);

   // if (lua_pcall(L, 2, 1, 0) != 0)
   // {
      //error(L, "error running function `f': %s",
      //  lua_tostring(L, -1));
 //   }
  }
}

void Player::addCommand(Command* command)
{
  command->player = this;
  commands.push_back(command);
}

void Player::lua_addCommand(std::string name)
{
  lua_commands.push_back(name);
}


//void Player::assignActor(Actor* actor)
//{
//  actor->owner = this;
//  this->assignedActor = actor;
//}
//
//void Player::unAssignActor()
//{
//  if (this->assignedActor != nullptr)
//  {
//    this->assignedActor->owner = nullptr;
//    this->assignedActor = nullptr;
//  }
//}

//Actor* Player::getAssignedActor()
//{
//  return assignedActor;
//}


void Player::removeCommand(const ushort commandID)
{
  for (unsigned int i=0; i<commands.size(); i++)
  {
    if (commands[i]->commandID == commandID)
    {
      delete commands[i];
      commands.erase(commands.begin() + i);
      return;
    }
  }
}

bool Player::hasCommand(const ushort commandID) const
{
  for (unsigned int i = 0; i < commands.size(); i++)
  {
    if (commands[i]->commandID == commandID)
    {
      return true;
    }
  }
  return false;
}