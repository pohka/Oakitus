#include "inventory_menu.h"

using namespace game::ui;
using namespace game;
using namespace oak::ui;



InventoryMenu::InventoryMenu()
{
  align.x = UI_ALIGN_HORZ_CENTER;
  align.y = UI_ALIGN_VERT_MIDDLE;

  background = new UIImage("inventory_bg.png", 700, 400);

  addNode(background);
}

InventoryMenu::~InventoryMenu()
{

}

//update the props before rendering
void InventoryMenu::onBeforeRender()
{

}