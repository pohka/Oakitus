#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>
#include <components/animator.h>
#include "game_def.h"
#include <core/base_player.h>
#include <event/event_manager.h>
#include "events/e_damage_taken.h"
#include "events/e_death.h"
#include "inventory.h"
#include "systems/modifier.h"

class oak::Entity;

namespace game
{
  class Player;
  class Ability;

  class Unit : public oak::Entity, public DamageTakenListener, public DeathListener
  {

   // oak::BasePlayer* owner;
    uint ownerID;
    bool m_hasOwner = false;
    float moveSpeed;
    static const float BASE_MOVE_SPEED;
    
    int health;
    oak::Animator* animator;
    bool m_isOwnerBotPlayer = false;
    
    //modifiers currently applied to this unit
    std::vector<Modifier*> modifiers;

    public:
      Unit();
      virtual ~Unit();

      oak::BasePlayer* getOwner() const;
      bool hasOwner() const;
      void setOwner(uint playerID);
      void removeOwner();
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


      void addModifier(uint casterID, Modifier* modifier);

      void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();

    protected:
      uchar faction;
      
      void onDamageTaken(DamageData& data) override;
      void onDeath(DeathData& data) override;

      Inventory inventory = Inventory(getID());
      std::vector<Ability*> abilitys;

    private:
      
      
  };

  
}

#endif