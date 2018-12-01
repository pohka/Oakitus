#ifndef ABILITY_H
#define ABILITY_H

#include "unit.h"
#include <core/id_generator.h>
#include <core/types.h>

namespace game
{
  class Unit;

  cnum CAST_STATE_NONE =    0;
  cnum CAST_STATE_PRECAST = 1;
  cnum CAST_STATE_CASTING = 2;

  cnum TARGET_TYPE_NONE =         0;
  cnum TARGET_TYPE_NO_TARGET =    1;
  cnum TARGET_TYPE_POINT =        2;
  cnum TARGET_TYPE_UNIT_TARGET =  3;


  cnum TARGET_TEAM_NONE =      0;
  cnum TARGET_TEAM_FRIENDLY =  1;
  cnum TARGET_TEAM_ENEMY =     2;
  cnum TARGET_TEAM_BOTH =      3;

  struct Target
  {
    uint targetEntityID = 0;
    glm::vec2 point = glm::vec2(0.0f, 0.0f);
  };


  class Ability
  {
    static oak::IDGenerator idGen;
    uint id;
    float startTime;
    float endTime;

    public:
      Ability();
      virtual ~Ability() = default;
      Unit* caster;
      void castOnTarget(Unit& unit);
      void castOnPoint(glm::vec2 point);
      void castNoTarget();

      uchar getCastState() const;
      uchar getTargetType() const;
      uint getID() const;
      float getStartTime() const;
      float getEndTime() const;

      virtual void onCast(); //when casting was successfully requested
      virtual void onAbilityStart(); //when the precast ends
      virtual void onAbilityEnd(); //when the cast time ends

      void setCastState(uchar state);

    protected:
      Target target;
      float preCastTime = 0.0f; //wind up before casting
      float castTime = 0.0f; //time to cast the ability
      uchar castState = 0;
      uchar targetType = 0;
      uchar targetTeam = 0;
      
    private:
      void beginCasting();
  };
}
#endif