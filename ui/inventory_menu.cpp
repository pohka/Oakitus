#include "inventory_menu.h"
#include <core/player_resource.h>
#include "../player.h"
#include "ui_templates.h"

using namespace game::ui;
using namespace game;
using namespace oak::ui;



InventoryMenu::InventoryMenu()
{
  align.x = UI_ALIGN_HORZ_CENTER;
  align.y = UI_ALIGN_VERT_MIDDLE;

  background = new UIImage("inventory_bg.png", 700, 400);
  background->offset.x = -(float)(background->w / 2);
  background->offset.y = (float)(background->h / 2);

  addNode(background);

  itemList = new UIDiv();
  background->addChild(itemList);

}

InventoryMenu::~InventoryMenu()
{

}

//update the props before rendering
void InventoryMenu::onBeforeRender()
{
  Player *player = static_cast<Player*>(oak::PlayerResource::getLocalPlayer());
  Unit* unit = player->getAssignedUnit();
  if (unit != nullptr)
  {
    std::vector<Item*>& items = unit->getInventory().getAllItems();

    for (uint i=0; i<items.size(); i++)
    {
      if (i >= itemList->children.size())
      {
        UINode* node = UITemplates::newInventoryItem(items[i]);
        itemList->addChild(node);
      }
      else
      {
        UITemplates::updateInventoryItem(itemList->children[i], items[i]);
      }
    }
  }
}