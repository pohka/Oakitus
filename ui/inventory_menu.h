#ifndef INVENTORY_MENU_H
#define INVENTORY_MENU_H

//#include <ui/ui_component.h>
#include <ui/ui.h>


namespace game
{
  //example ui component
  class InventoryMenu : public ion::UIComponent
  {
    ion::UIImage* background;
    ion::UIDiv* itemList;

    public:
      InventoryMenu();
      ~InventoryMenu();

      //update the props before rendering
      void onBeforeRender() override;
  };
}

#endif