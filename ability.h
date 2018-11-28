#ifndef ABILITY_H
#define ABILITY_H

#include "unit.h"


namespace game
{
  class Unit;

  enum CastingState 
  {
    NONE,
    PRECAST,
    CASTING
  };

  enum TargetType 
  {
    NO_TARGET,
    POINT,
    UNIT_TARGET
  };

  struct Target
  {
    uint targetEntityID = 0;
    glm::vec2 point = glm::vec2(0.0f, 0.0f);
  };


  class Ability
  {
    public:
      virtual ~Ability() = default;
      Unit* caster;
      void castOnTarget(Unit& unit);
      void castOnPoint(glm::vec2 point);
      void castNoTarget();

      CastingState getCastingState() const;
      TargetType getTargetType() const;

      virtual void onCast(); //when casting was successfully requested
      virtual void onAbilityStart(); //when the precast ends
      virtual void onAbilityEnd(); //when the cast time ends


    protected:
      Target target;
      float preCastTime = 0.0f; //wind up before casting
      float castTime = 0.0f; //time to cast the ability
      CastingState castingState = CastingState::NONE;
      TargetType targetType = TargetType::NO_TARGET;
      
  };
}
#endif