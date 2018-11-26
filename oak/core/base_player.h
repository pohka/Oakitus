#ifndef BASE_PLAYER_H
#define BASE_PLAYER_H

#include "id_generator.h"
#include "types.h"
#include <vector>
#include "command.h"

namespace oak
{

  class BasePlayer
  {
    static oak::IDGenerator idGen;
    uint playerID;
    
    
    

    public :
      

      BasePlayer();
      ~BasePlayer();

      uint getID();
      void executeCommands();

    protected:
      std::vector<Command> commands;
  };
}

#endif