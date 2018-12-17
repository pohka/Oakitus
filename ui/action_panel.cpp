#include "action_panel.h"
#include <ui/ui_image.h>
#include <ui/ui_label.h>
#include "../strings_def.h"
#include <debug.h>
#include <core/player_resource.h>
#include "../player.h"

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
  label->offset.y = 70.0f;
 // label->text = Localization::strings[STRING_HEALTH] + std::to_string(prop_hp);
  nodes.push_back(label);

  label2 = UILabel::createLabel("", 20, 400, 20);
  label2->color = { 0.9f, 0.9f, 0.9f };
  label2->offset.x = 30.0f;
  label2->offset.y = 50.0f;
 // label2->text = Localization::strings[STRING_MANA] + std::to_string(prop_hp);
  nodes.push_back(label2);
}

ActionPanel::~ActionPanel()
{

}

void ActionPanel::onBeforeRender()
{
  Player* player = static_cast<Player*>(oak::PlayerResource::getLocalPlayer());
  Unit* unit = player->getAssignedUnit();
  if (unit != nullptr)
  {
    prop_hp = unit->getHealth();
    label->text = Localization::strings[STRING_HEALTH] + std::to_string(prop_hp) + "/" + std::to_string(unit->getMaxHealth());

    prop_mana = unit->getMana();
    label2->text = Localization::strings[STRING_MANA] + std::to_string(prop_mana) + "/" + std::to_string(unit->getMaxMana());
  }
}
