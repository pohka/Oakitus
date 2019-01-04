#ifndef COMMAND_CAST_ABILITYS_H
#define COMMAND_CAST_ABILITYS_H

#include <oak/core/command.h>
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
        glm::vec3 getCasterPosition() const;
        void beginCast(const int index) const;
    };
  }
}
#endif