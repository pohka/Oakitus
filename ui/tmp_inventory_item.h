#ifndef TMP_INVENTORY_ITEM_H
#define TMP_INVENTORY_ITEM_H

#include <ui/ui.h>
#include "../systems/item.h"



namespace game
{


  struct tmp_InventoryItem : public oak::ui::UIDiv
  {
    tmp_InventoryItem(Item* item);
    void update(Item* item);
    static void onItemFocus(UINode* node);
  };

}

#endif