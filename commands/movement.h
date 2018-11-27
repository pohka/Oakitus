#ifndef COMMAND_MOVEMENT_H
#define COMMAND_MOVEMENT_H

#include <core/command.h>
#include "../player.h"

namespace game
{
  namespace command
  {
    class Movement : public oak::Command
    {
      game::Player* player;

    public:
      Movement(game::Player& player);
      ~Movement();

      void execute() override;
    };
  }
}

#endif
