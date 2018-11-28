#ifndef BASE_PLAYER_H
#define BASE_PLAYER_H

#include "id_generator.h"
#include "types.h"
#include <vector>
#include "command.h"

namespace oak
{
  class Command;

  class BasePlayer
  {
    static oak::IDGenerator idGen;
    uint playerID;
    
    
    public :
      BasePlayer();
      virtual ~BasePlayer();

      uint getID() const;
      void executeCommands();
      void addCommand(Command& command);

    protected:
      std::vector<Command*> commands;
  };
}

#endif