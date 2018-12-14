#ifndef INVENTORY_H
#define INVENTORY_H

#include "systems/item.h"
#include <vector>
#include "systems/kv_array.h"

namespace game
{
  class Inventory
  {
    //typedef std::pair<uchar, Item*> Slot;

    std::vector<Item*> items;
    oak::kv_array<uchar, Item*, 4> slots;
    //Slot slots[1];

    public:
      Inventory();
      ~Inventory();
      void addItem(Item* item);
      Item* getItem(uint itemID);
      void equipItem(uint itemID);
      void unEquipItem(uint itemID);
  };
}

#endif