#ifndef ACTION_PANEL_H
#define ACTION_PANEL_H

#include <ui/ui_component.h>
#include <ui/ui_label.h>

namespace game
{
  namespace ui
  {
    class ActionPanel: public oak::ui::UIComponent
    {
      int prop_hp;
      oak::ui::UILabel* label;

      public:
        ActionPanel();
        ~ActionPanel();
      
      
        void setHP(int hp);
    };
  }
}

#endif