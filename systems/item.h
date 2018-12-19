#ifndef ITEM_H
#define ITEM_H

#include <core/types.h>
#include "../game_def.h"
#include "modifier.h"
#include "../strings_def.h"

namespace game
{
  struct Item
  {
    //quality
    uchar quality = ITEM_QUALITY_COMMON;

    //price
    int price = 0;

    //player can sell the item
    bool isSellable = true;

    //player can destroy the item
    bool isDestroyable = true;

    //stacks in inventroy UI, must be possible to have multiple instances of the same item in the inventory
    bool isStackable = false; 

    //item slot
    uchar slot = ITEM_SLOT_NONE;

    //name string id
    uint nameSID;

    //modifiers this item can use
    //std::vector<Modifier*> modifiers;

    uint getItemID();

    uint ownerID;

    std::string name;

    virtual void onEquip() = 0;
    virtual void onUnEquip() = 0;

    private:
      uint itemID;
  };
}

#endif