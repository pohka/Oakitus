#include "ui_templates.h"

using namespace game;
using namespace game::ui;
using namespace oak::ui;

oak::ui::UINode* UITemplates::newInventoryItem(Item* item)
{
  UILabel* label = new UILabel(item->name, 20);
  label->margin.x = 10.0f;
  label->margin.y = 5.0f;
  return label;
}

void UITemplates::updateInventoryItem(UINode* node, Item* item)
{
  UILabel* label = static_cast<UILabel*>(node);
  label->text = item->name;
}
