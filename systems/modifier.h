#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>
#include "../abilitys/modifiers/modifier_def.h"

namespace game
{
  //instance
  struct Modifier
  {
    Modifier(ushort id);
    bool isPassive = false; //if true, duration is ignored
    bool isHidden = false; //shows in the modifier ui
    bool isStackable = false;
    bool isDebuff = true;
    uchar stackCount = 1;
    uchar maxStacks = 1;
    float duration = 0.0f;

    std::unordered_map<uchar, int> props;
    uint casterID;

    void setProp(uchar propertyID, int value);
    uint getModifierID();
    void refresh();

    //events
    virtual void onCreated() = 0;

    //protected:
      

    private:
      ushort modifierID;
      float startTime;
      float endTime;
    
  };
}

#endif