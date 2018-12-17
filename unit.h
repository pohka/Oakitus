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
    uint ownerID;
    bool m_hasOwner = false;
    
    //stats
    float health = 100.0f;
    float mana = 100.0f;
    int moveSpeed = 100;
    int damage = 10;
    int resist[ELEMENT_COUNT] = {};
    int amplify[ELEMENT_COUNT] = {};
    float healthRegen = 0;
    float manaRegen = 0;
    int maxHealth = 100;
    int maxMana = 100;
    
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
      int getMoveSpeed() const;
      void setMoveSpeed(int moveSpeed);
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
      int getResist(uchar element);
      int getAmplify(uchar element);
      int getMana();
      void useMana(int amount);
      int getMaxHealth();
      int getMaxMana();
      void setManaRegen(float manaPerSecond);
      void setHealthRegen(float healthPerSecond);
      float getManaRegen();
      float getHealthRegen();
      void heal(int amount);
      

      void addModifier(uint casterID, Modifier* modifier);
      //if this unit has a matching modifier, removes it note:does not call onDestroy()
      void removeModifier(ushort modifierID, uint casterID); 
      std::vector<Modifier*>& getAllModifiers();

      void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();

      static Unit* findUnit(uint unitID);

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