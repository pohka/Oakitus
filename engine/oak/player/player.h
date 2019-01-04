#ifndef PLAYER_H
#define PLAYER_H

#include <oak/ecs/id_generator.h>
#include <oak/core/types.h>
#include <vector>
#include "command.h"
#include <oak/ecs/actor.h>

namespace oak
{
  class Command;
  class Actor;

  ///<summary>BasePlayer class for player input and can be extended for more functionality</summary>
  //Preferrably Player instances should be added to the PlayerResource class as
  //they can be easily accessed and managed through the PlayerResource class
  class Player
  {
    static oak::IDGenerator idGen; ///<summary>Player Unique ID generator</summary>
    uint playerID; ///<summary>Player Unique ID</summary>
    Actor* assignedActor;
    
    public :
      Player();
      virtual ~Player();

      ///<summary>Returns the playerID</summary>
      uint getPlayerID() const;

      ///<summary>Calls execute() on all the Commands for this Player</summary>
      void executeCommands();

      ///<summary>Adds an input Command to this Player</summary>
      void addCommand(Command* command);
      void removeCommand(const ushort commandID);
      bool hasCommand(const ushort commandID) const;

      void assignActor(Actor* actor);
      Actor* getAssignedActor();
      void unAssignActor();

    protected:
      ///<summary>All of the commands for this Player</summary>
      std::vector<Command*> commands;
  };
}

#endif