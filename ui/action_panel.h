#ifndef ACTION_PANEL_H
#define ACTION_PANEL_H

#include <ui/ui_component.h>
#include <ui/ui_label.h>

namespace game
{
  //example ui component
  class ActionPanel: public ion::UIComponent
  {
    int prop_hp;
    int prop_mana;
    ion::UILabel* label;
    ion::UILabel* label2;

    public:
      ActionPanel();
      ~ActionPanel();
      
      //update the props before rendering
      void onBeforeRender() override;
  };
}

#endif