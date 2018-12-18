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
  
  UINode* img = new UIImage("action_panel.png", 440, 64);
  img->offset.x = 10.0f;
  img->offset.y = 80.0f;
  addNode(img);

  label = new UILabel("", 20, 400, 20);
  label->color = { 0.9f, 0.9f, 0.9f };
  label->offset.x = 10.0f;
  label->offset.y = -5.0f;
  img->addChild(label);

  label2 = new UILabel("", 20, 400, 20);
  label2->color = { 0.9f, 0.9f, 0.9f };
  label2->offset.x = 10.0f;
  label2->offset.y = -25.0f;
  img->addChild(label2);
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
    prop_hp = (int)unit->getHealth();
    label->text = Localization::strings[STRING_HEALTH] + std::to_string(prop_hp) + "/" + std::to_string((int)unit->getMaxHealth());

    prop_mana = (int)unit->getMana();
    label2->text = Localization::strings[STRING_MANA] + std::to_string(prop_mana) + "/" + std::to_string((int)unit->getMaxMana());
  }
}
