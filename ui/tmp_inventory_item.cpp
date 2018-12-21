#include "tmp_inventory_item.h"
#include <debug.h>
//#include <ui/style.h>

using namespace game;
using namespace oak::ui;



tmp_InventoryItem::tmp_InventoryItem(Item* item) : UIDiv()
{
  inlineStyle->attrs[oak::style::width] = 200.0f;
  this->onFocus = tmp_InventoryItem::onItemFocus;

  UILabel* label = new UILabel(item->name, 20);
  label->inlineStyle->setMargin(30.0f, 10.0f);
  label->calcStyle();
  addChild(label);
  

  UIImage* equipedIcon = new UIImage("default.png", 16, 16);
  //todo: fix next line
  //equipedIcon->offset.y += (float)(label->getTotalH() - ((label->getTotalH() - equipedIcon->h)/2));
 // LOG << "offsetY:" << equipedIcon->offset.y;
 // equipedIcon->offset.x = 10.0f;
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
  LOG << "focus:" << (int)node->getType();
  UILabel* label = static_cast<UILabel*>(node->children[0]);
  label->inlineStyle->color = COLOR_RED;
  label->calcStyle();
}

