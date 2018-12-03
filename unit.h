#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>
#include <components/animator.h>
#include "game_def.h"


class oak::Entity;

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
    int health;
    oak::Animator* animator;

    public:
      Unit();
      virtual ~Unit();

      Player* getOwner() const;
      bool hasOwner() const;
      float getMoveSpeed() const;
      void setMoveSpeed(float moveSpeed);
      void addAbility(Ability* ability);
      Ability* getAbilityByIndex(uint index) const;
      uchar getFaction() const;
      int getHealth() const;
      void setHealth(int hp);
      void applyDamage(int amount, uint attackerID, uint abilityID);
      bool isAlive() const;
      
      void addAnimator(oak::Animator* animator);
      void setAnimation(uchar animType);
      uchar getAnimDirection() const;
      void setAnimDirection(uchar direction);

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();

    protected:
      uchar faction;
      

    private:
      void onDeath();
  };

  
}

#endif