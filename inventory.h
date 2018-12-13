#ifndef INVENTORY_H
#define INVENTORY_H

#include "systems/item.h"
#include <vector>

namespace game
{
  class Inventory
  {
    std::vector<Item*> items;

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