#ifndef ABILITY_H
#define ABILITY_H

namespace game
{
  class Ability
  {
    public:
    //  Ability();
    //  ~Ability();

      virtual void cast(float x, float y) = 0;
  };
}
#endif