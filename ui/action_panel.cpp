#include "action_panel.h"
#include <ui/ui_image.h>
#include <ui/ui_label.h>
#include "../strings_def.h"
#include <debug.h>

using namespace game::ui;
using namespace oak::ui;



ActionPanel::ActionPanel()
{
  prop_hp = 100;

  align.x = UI_ALIGN_HORZ_LEFT;
  align.y = UI_ALIGN_VERT_BOTTOM;
  
  UINode* img = UIImage::createImage("action_panel.png", 440, 64);
  img->offset.x = 220.0f;
  img->offset.y = 45.0f;
  nodes.push_back(img);

  label = UILabel::createLabel("", 20, 400, 20);
  label->color = { 0.9f, 0.9f, 0.9f };
  label->offset.x = 30.0f;
  label->offset.y = 60.0f;
  label->text = Localization::strings[STRING_HEALTH] + std::to_string(prop_hp);
  nodes.push_back(label);

  label2 = UILabel::createLabel("", 20, 400, 20);
  label2->color = { 0.9f, 0.9f, 0.9f };
  label2->offset.x = 150.0f;
  label2->offset.y = 60.0f;
  label2->text = Localization::strings[STRING_MANA] + std::to_string(prop_hp);
  nodes.push_back(label2);
}

ActionPanel::~ActionPanel()
{

}

void ActionPanel::setHP(int hp)
{
  LOG << "setting hp";
  prop_hp = hp;
  label->text = Localization::strings[STRING_HEALTH] + std::to_string(prop_hp);
}

void ActionPanel::setMana(int mana)
{
  LOG << "setting hp";
  prop_mana = mana;
  label2->text = Localization::strings[STRING_MANA] + std::to_string(prop_mana);
}