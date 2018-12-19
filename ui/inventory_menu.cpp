#include "inventory_menu.h"
#include <core/player_resource.h>
#include "../player.h"

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
      if (i >= background->children.size())
      {
        UILabel* label = new UILabel(items[i]->name, 20, 100, 24);
        label->offset.y = -(float)(label->h * i);
        background->addChild(label);
      }
      else
      {
        UILabel* label = static_cast<UILabel*>(background->children[i]);
        label->text = items[i]->name;
        label->offset.y = -(float)(label->h * i);
      }
      
    }
  }
}