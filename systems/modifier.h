#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>

namespace game
{
  //instance
  struct Modifier
  {
    bool isPassive = false; //if true, duration is ignored
    bool isHidden = false; //shows in the modifier ui
    bool isStackable = false;
    bool isDebuff = true;
    uchar stackCount = 1;
    uchar maxStacks = 1;
    float duration = 0.0f;

    std::unordered_map<uchar, int> properties;
    uint casterID;

    void addProperty(uchar propertyID, int value);
    uint getModifierID();
    void refresh();

    //events
    virtual void onCreated() = 0;

  private:
    uint modifierID;
    float startTime;
    float endTime;
    
  };
}

#endif