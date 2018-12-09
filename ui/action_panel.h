#ifndef ACTION_PANEL_H
#define ACTION_PANEL_H

#include <ui/ui_component.h>

namespace game
{
  namespace ui
  {
    struct ActionPanel : public oak::ui::UIComponent
    {
      ActionPanel();
      int prop_hp;
      
    };
  }
}

#endif