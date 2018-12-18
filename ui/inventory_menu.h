#ifndef INVENTORY_MENU_H
#define INVENTORY_MENU_H

//#include <ui/ui_component.h>
#include <ui/ui.h>

namespace game
{
  namespace ui
  {
    //example ui component
    class InventoryMenu : public oak::ui::UIComponent
    {
      oak::ui::UIImage* background;

    public:
      InventoryMenu();
      ~InventoryMenu();

      //update the props before rendering
      void onBeforeRender() override;
    };
  }
}

#endif