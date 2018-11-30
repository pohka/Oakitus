#ifndef UNIT_H
#define UNIT_H

#include <core/entity.h>



class oak::Entity;

namespace game
{
  class Player;
  class Ability;

  enum Faction
  {
    NO_FACTION,
    PLAYER,
    ENEMY
  };

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
      Faction getFaction() const;
      

      //void onStart() override;
      //void onDestroy() override;
      //void onDraw() override;
      void onUpdate();

    protected:
      Faction faction;
  };

  
}

#endif