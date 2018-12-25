#include "action_panel.h"
#include <oak/ui/ui_image.h>
#include <oak/ui/ui_label.h>
#include "../strings_def.h"
#include <oak/debug.h>
#include <oak/core/player_resource.h>
#include "../player.h"

using namespace game;
using namespace ion;


ActionPanel::ActionPanel()
{
  align.x = UI_ALIGN_HORZ_LEFT;
  align.y = UI_ALIGN_VERT_BOTTOM;
  
  UINode* img = new UIImage("action_panel.png", 440, 64);
  img->style.setPadding(40.0f, 0.0f);
  img->style.set(STYLE_MARGIN_TOP, -80.0f);
  addNode(img);

  label = new UILabel("", 20);
  label->style.color = { 0.9f, 0.9f, 0.9f, 1.0f };
  label->style.setMargin(10.0f, 4.0f);
  img->addChild(label);

  label2 = new UILabel("", 20);
  label2->style.color = { 1.0f, 1.0f, 0.0f, 1.0f };
  label2->style.setMargin(10.0f, 4.0f);
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
