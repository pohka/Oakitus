#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>

namespace game
{
  class Modifier
  {
    uint modifierID;
    float startTime;
    float endTime;
    float duration;
    

    public:
      bool isPassive; //if true, duration is ignored
      bool isHidden; //shows in the modifier ui
      std::unordered_map<uchar, int> properties;
      
      Modifier(float duration = 0, bool isPassive = true, bool isHidden = true);
      ~Modifier();

      void addProperty(uchar propertyID, int value);

      uint getModifierID();
      bool getIsPassive();
      bool getIsHidden();
  };
}

#endif