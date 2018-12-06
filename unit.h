#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>
#include <components/animator.h>
#include "game_def.h"
#include <core/base_player.h>
#include <event/event_manager.h>
#include "events/e_damage_taken.h"
#include "events/e_death.h"

class oak::Entity;

namespace game
{
  class Player;
  class Ability;

  class Unit : public oak::Entity, public DamageTakenListener, public DeathListener
  {

    oak::BasePlayer* owner;
    float moveSpeed;
    static const float BASE_MOVE_SPEED;
    std::vector<Ability*> abilitys;
    int health;
    oak::Animator* animator;
    bool m_isOwnerBotPlayer = false;

    public:
      Unit();
      virtual ~Unit();

      oak::BasePlayer* getOwner() const;
      bool hasOwner() const;
      float getMoveSpeed() const;
      void setMoveSpeed(float moveSpeed);
      void addAbility(Ability* ability);
      Ability* getAbilityByIndex(uint index) const;
      uchar getFaction() const;
      int getHealth() const;
      void setHealth(int hp);
      bool isAlive() const;
      bool isOwnerBotPlayer() const;
      
      void addAnimator(oak::Animator* animator);
      void setAnimation(uchar animType);
      uchar getAnimDirection() const;
      void setAnimDirection(uchar direction);

      void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();

    protected:
      uchar faction;
      
      void onDamageTaken(DamageData& data) override;
      void onDeath(DeathData& data) override;
    private:
      
      
  };

  
}

#endif