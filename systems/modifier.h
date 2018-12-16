#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>

#include "../abilitys/modifiers/modifier_def.h"

namespace game
{
  class Unit;

  //instance
  struct Modifier
  {
    Modifier(ushort id);
    void init(Unit* owner, uint attackerID);

    bool destroyOnExpire = true;
    bool isHidden = false; //shows in the modifier ui
    bool isStackable = false;
    bool isDebuff = true;
    uchar stackCount = 1;
    uchar maxStacks = 1;
    float duration = 0.0f;

    std::unordered_map<uchar, int> props;
    uint attackerID;

    void setProp(uchar propertyID, int value);
    uint getModifierID();
    void refresh();
    

    //events
    virtual void onCreated() = 0;
    void onUpdate();
    virtual void onDestroy() = 0;
    virtual void onDeath() = 0;
    virtual void onRefresh() = 0;
    float getEndTime();

    protected:
      Unit* owner;

    private:
      ushort modifierID;
      float startTime;
      float endTime;
      
    
  };
}

#endif