#ifndef ACTION_PANEL_H
#define ACTION_PANEL_H

#include <ui/ui_component.h>
#include <ui/ui_label.h>

namespace game
{
  namespace ui
  {
    //example ui component
    class ActionPanel: public oak::ui::UIComponent
    {
      int prop_hp;
      int prop_mana;
      oak::ui::UILabel* label;
      oak::ui::UILabel* label2;

      public:
        ActionPanel();
        ~ActionPanel();
      
       //updating ui prop for HP
       void setHP(int hp);
       void setMana(int mana);
    };
  }
}

#endif