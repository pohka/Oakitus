#include "tmp_inventory_item.h"
#include <debug.h>

using namespace game;
using namespace ion;


tmp_InventoryItem::tmp_InventoryItem(Item* item) : UIDiv()
{
  style->set(STYLE_WIDTH, 200.0f);
  this->addClass("inv-item");
  this->onFocus = tmp_InventoryItem::onItemFocus;

  UILabel* label = new UILabel(item->name, 20.0f);
  label->style->setMargin(30.0f, 4.0f);
  label->addClass("inv-item-text");
  addChild(label);
  

  UIImage* equipedIcon = new UIImage("default.png", 16, 16);
  equipedIcon->style->set(STYLE_MARGIN_TOP, -20.0f);
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

void tmp_InventoryItem::onItemFocus(UINode* node)
{
  //LOG << "focus:" << (int)node->getType();
  UILabel* label = static_cast<UILabel*>(node->children[0]);
  label->style->color = COLOR_RED;
  label->computeStyle();
}

