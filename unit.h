#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>

#include "player.h"
#include "ability.h"

namespace game
{
  class Player;

  class Unit : public oak::Entity
  {

    Player* owner;
    float moveSpeed;
    static const float BASE_MOVE_SPEED;
    std::vector<Ability*> abilitys;

    public:
      Unit();
      ~Unit();

      Player* getOwner();
      bool hasOwner();
      float getMoveSpeed();
      void setMoveSpeed(float moveSpeed);
      void addAbility(Ability& ability);
      Ability* getAbilityByIndex(uint index);

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      //void onUpdate() override;
  };

  
}

#endif