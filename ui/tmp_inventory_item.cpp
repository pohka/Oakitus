#include "tmp_inventory_item.h"

using namespace game;
using namespace oak::ui;

tmp_InventoryItem::tmp_InventoryItem(Item* item) : UIDiv()
{
  UILabel* label = new UILabel(item->name, 20);
  label->margin.x = 10.0f;
  label->margin.y = 5.0f;
  addChild(label);
}

void tmp_InventoryItem::update(Item* item)
{
  UILabel* label = static_cast<UILabel*>(children[0]);
  label->text = item->name;
}