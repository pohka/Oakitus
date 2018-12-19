#ifndef UI_TEMPLATES_H
#define UI_TEMPLATES_H

#include <ui/ui.h>
#include "../systems/item.h"

namespace game
{
  namespace ui
  {
    struct UITemplates
    {
      static oak::ui::UINode* newInventoryItem(game::Item* item);
      static void updateInventoryItem(oak::ui::UINode* node, game::Item* item);
    };
  }
}

#endif