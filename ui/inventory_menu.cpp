#include "inventory_menu.h"
#include <core/player_resource.h>
#include "../player.h"
#include "tmp_inventory_item.h"

using namespace game;
using namespace ion;


InventoryMenu::InventoryMenu()
{
  align.x = UI_ALIGN_HORZ_CENTER;
  align.y = UI_ALIGN_VERT_MIDDLE;

  background = new UIImage("inventory_bg.png", 700, 400);
  background->style->set(STYLE_MARGIN_LEFT, -350.0f);
  background->style->set(STYLE_MARGIN_TOP, -200.0f);
  //background->computeStyle();
  addNode(background);

  itemList = new UIDiv();
  itemList->style->setMargin(40.0f, 40.0f);
  //itemList->computeStyle();
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
        UINode* node = new tmp_InventoryItem(items[i]);
        itemList->addChild(node);
      }
      else
      {
        tmp_InventoryItem* tmp_item = static_cast<tmp_InventoryItem*>(itemList->children[i]);
        tmp_item->update(items[i]);
      }
    }
  }
}