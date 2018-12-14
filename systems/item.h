#ifndef ITEM_H
#define ITEM_H

#include <core/types.h>
#include "../game_def.h"
#include <unordered_map>
#include "modifier.h"
#include "../strings_def.h"

namespace game
{
  class Item
  {
    uint itemID;

    public:
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

      //modifiers
      std::vector<ModifierData> modifiers;

      Item();
      ~Item();
      uint getItemID();
  };
}

#endif