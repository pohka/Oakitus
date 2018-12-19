#include "tmp_inventory_item.h"
#include <debug.h>

using namespace game;
using namespace oak::ui;

tmp_InventoryItem::tmp_InventoryItem(Item* item) : UIDiv()
{
  UILabel* label = new UILabel(item->name, 20);
  label->margin.x = 30.0f;
  label->margin.y = 10.0f;
  addChild(label);
  //label->onFocus = &this->onItemFocus;

  UIImage* equipedIcon = new UIImage("default.png", 16, 16);
  equipedIcon->offset.y += (float)(label->getTotalH() - ((label->getTotalH() - equipedIcon->h)/2));
  LOG << "offsetY:" << equipedIcon->offset.y;
  equipedIcon->offset.x = 10.0f;
  equipedIcon->positionType = UI_POSITION_ABSOLUTE;
  addChild(equipedIcon);
}

void tmp_InventoryItem::update(Item* item)
{
  UILabel* label = static_cast<UILabel*>(children[0]);
  if (item->isEquiped)
  {
    UIImage* icon = static_cast<UIImage*>(children[1]);
    icon->setTexture("face.png");
  }
  label->text = item->name;
}

void tmp_InventoryItem::onItemFocus()
{
  UILabel* label = static_cast<UILabel*>(children[0]);
  label->color = COLOR_RED;
}

