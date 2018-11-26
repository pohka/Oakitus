#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>

#include "player.h"

namespace game
{
  class Player;

  class Unit : public oak::Entity
  {

    Player* owner;

    public:
      Unit();
      ~Unit();

      Player* getOwner();
     // void setOwner(Player& player);
      bool hasOwner();

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      //void onUpdate() override;
  };
}

#endif