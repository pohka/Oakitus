#ifndef ITEM_TEST_H
#define ITEM_TEST_H

#include "../systems/item.h"

namespace game
{
  struct ItemTest : public Item
  {
    ItemTest();

    void onEquip() override;
    void onUnEquip() override;
  };
}


#endif