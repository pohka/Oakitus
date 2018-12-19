#include "tmp_inventory_item.h"

using namespace game;
using namespace oak::ui;

tmp_InventoryItem::tmp_InventoryItem(Item* item) : UIDiv()
{
  UILabel* label = new UILabel(item->name, 20);
  label->margin.x = 30.0f;
  label->margin.y = 1.0f;
  addChild(label);

  UIImage* equipedIcon = new UIImage("default.png", 16, 16);
  equipedIcon->offset.y += 18.0f;
  equipedIcon->offset.x = 10.0f;
  equipedIcon->positionType = UI_POSITION_ABSOLUTE;
  addChild(equipedIcon);
}

void tmp_InventoryItem::update(Item* item)
{
  UILabel* label = static_cast<UILabel*>(children[0]);
  label->text = item->name;
}