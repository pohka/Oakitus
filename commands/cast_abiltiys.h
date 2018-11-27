#ifndef COMMAND_CAST_ABILITYS_H
#define COMMAND_CAST_ABILITYS_H

#include <core/command.h>
#include "../player.h"

namespace game
{
  namespace command
  {
    class CastAbilitys : public oak::Command
    {
      Player* player;

      public:
        CastAbilitys(Player& player);
        ~CastAbilitys();
        void execute() override;
      private:
        glm::vec3 getCasterPosition();
    };
  }
}
#endif