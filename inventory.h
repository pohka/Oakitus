#ifndef INVENTORY_H
#define INVENTORY_H

#include "systems/item.h"
#include <vector>
#include <core/kv_array.h>

namespace game
{
  class Inventory
  {
    //typedef std::pair<uchar, Item*> Slot;

    std::vector<Item*> items;
    oak::kv_array<uchar, Item*, 4> slots; //equiped slots
    uint ownerID;

    public:
      Inventory(uint ownerID);
      ~Inventory();
      void addItem(Item* item);
      Item* getItem(uint itemID);
      void equipItem(Item* item);
      void unEquipItem(uchar slotID);
      std::vector<Item*>& getAllItems();
  };
}

#endif