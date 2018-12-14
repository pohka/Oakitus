#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>

namespace game
{
  //data
  struct ModifierData
  {
    uint modifierID;
    bool isPassive= true; //if true, duration is ignored
    bool isHidden = true; //shows in the modifier ui
    bool isDebuff = false;
    bool isStackable = false;
    uchar maxStacks = 1;
    float duration = 0.0f;
    std::unordered_map<uchar, int> properties;

    void addProperty(uchar propertyID, int value)
    {
      properties.insert(std::pair<uchar, int>(propertyID, value));
    }
  };

  //instance
  class Modifier
  {
    uint modifierID;
    float startTime;
    float endTime;
    float duration;

    public:
      bool isPassive; //if true, duration is ignored
      bool isHidden; //shows in the modifier ui
      bool isStackable;
      bool isDebuff;
      uchar stackCount;
      uchar maxStacks;

      std::unordered_map<uchar, int> properties;
      
      Modifier(ModifierData& data);
      ~Modifier();

      void addProperty(uchar propertyID, int value);

      uint getModifierID();
      bool getIsPassive();
      bool getIsHidden();
      bool getIsDebuff();
  };
}

#endif