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
    float moveSpeed;
    static const float BASE_MOVE_SPEED;

    public:
      Unit();
      ~Unit();

      Player* getOwner();
      bool hasOwner();
      float getMoveSpeed();
      void setMoveSpeed(float moveSpeed);

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      //void onUpdate() override;
  };

  
}

#endif