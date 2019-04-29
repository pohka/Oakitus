#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <oak/ecs/id_generator.h>
#include <oak/core/types.h>
#include <vector>
#include "command.h"
#include <oak/ecs/entity.h>

namespace oak
{
  class Command;
  class Entity;
  //BasePlayer class for player input and can be extended for more functionality
  //Preferrably Player instances should be added to the PlayerResource class as
  //they can be easily accessed and managed through the PlayerResource class
  class Player
  {
    static oak::IDGenerator idGen; //Player Unique ID generator
    uint playerID; //Player Unique ID
    //Actor* assignedActor;
    std::vector<std::string> lua_commands;

    Entity* assignedEntity = nullptr;
    
    public :
      Player();
      virtual ~Player();

      //Returns the playerID
      uint getPlayerID() const;

      //Calls execute() on all the Commands for this Player
      void tickCommands();

      //Adds an input Command to this Player
      void addCommand(Command* command);
      //void lua_addCommand(std::string name);
      void removeCommand(const ushort commandID);
      bool hasCommand(const ushort commandID) const;

     // void assignActor(Actor* actor);
     // Actor* getAssignedActor();
     // void unAssignActor();

      void assignEntity(Entity* entity);
      void unassignEntity();
      Entity* getAssignedEntity();

    protected:
      //All of the commands for this Player
      std::vector<Command*> commands;
  };
}

#endif