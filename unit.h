#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>
#include <core/types.h>
#include <components/animator.h>


class oak::Entity;

namespace game
{
  class Player;
  class Ability;

  cnum ANIM_TYPE_NONE =       0;
  cnum ANIM_TYPE_IDLE =       1;
  cnum ANIM_TYPE_RUN =        2;
  cnum ANIM_TYPE_ATTACK =     3;
  cnum ANIM_TYPE_ABILITY_1 =  4;
  cnum ANIM_TYPE_ABILITY_2 =  5;
  cnum ANIM_TYPE_ABILITY_3 =  6;
  cnum ANIM_TYPE_ABILITY_4 =  7;


  cnum FACTION_NONE = 0;
  cnum FACTION_PLAYER = 1;
  cnum FACTION_ENEMY = 2;

  cnum ANIM_PRIORITY_LOWEST =   0;
  cnum ANIM_PRIORITY_BASE =     1;
  cnum ANIM_PRIORITY_ABILITY =  2;
  cnum ANIM_PRIORITY_DISABLE =  3;

  

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