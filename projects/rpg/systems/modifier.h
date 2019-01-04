#ifndef MODIFIER_H
#define MODIFIER_H

#include "../game_def.h"
#include <unordered_map>

#include "../abilitys/modifiers/modifier_def.h"

namespace game
{
  class Unit;

  //struct for tracking modifier ticks
  struct ModifierTicker
  {
    float interval;
    float nextTickTime;
    bool isTicking = false;
  };

  //instance
  struct Modifier
  {
    Modifier(ushort id);
    void init(Unit* owner, uint casterID);

    bool destroyOnExpire = true;
    bool isHidden = false; //shows in the modifier ui
    bool isStackable = false;
    bool isDebuff = true;
    uchar stackCount = 1;
    uchar maxStacks = 1;
    float duration = 0.0f;
    uchar elementType = ELEMENT_NORMAL;

    std::unordered_map<uchar, int> props;
    uint casterID;

    void setProp(uchar propertyID, int value);
    uint getModifierID();
    void refresh();

    //call onDestroy() and remove this modifier from its owner
    void destroy();
    

    //events
    virtual void onCreated() = 0;
    void onUpdate();
    virtual void onDestroy() = 0;
    virtual void onDeath() = 0;
    virtual void onRefresh() = 0;
    virtual void onIntervalTick();
    float getEndTime();

    protected:
      Unit* owner;
      void startTicker(float interval);

    private:
      ushort modifierID;
      float startTime;
      float endTime;
      ModifierTicker ticker;
  };
}

#endif