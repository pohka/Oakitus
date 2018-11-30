#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>

#include "player.h"
#include "ability.h"

namespace game
{
  class Player;
  class Ability;

  class Unit : public oak::Entity
  {

    Player* owner;
    float moveSpeed;
    static const float BASE_MOVE_SPEED;
    std::vector<Ability*> abilitys;

    public:
      Unit();
      virtual ~Unit();

      Player* getOwner() const;
      bool hasOwner() const;
      float getMoveSpeed() const;
      void setMoveSpeed(float moveSpeed);
      void addAbility(Ability* ability);
      Ability* getAbilityByIndex(uint index) const;
      

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();
  };

  
}

#endif