#include "status.h"
#include <oak/ui/ui_image.h>
#include <oak/ui/ui_label.h>
#include <oak/debug.h>
#include <oak/player/player_resource.h>
#include <oak/components/unit.h>
#include <oak/ui/ui_def.h>

using namespace oak;
using namespace game;
using namespace ion;


Status::Status()
{
  align.x = UI_ALIGN_HORZ_CENTER;
  align.y = UI_ALIGN_VERT_BOTTOM;

  //UINode* img = new UIImage("action_panel.png", 440, 64);
  //img->style.setPadding(40.0f, 0.0f);
  //img->style.set(STYLE_MARGIN_TOP, -80.0f);
  //addNode(img);

  label = new UILabel("", 20);
  label->style.color = { 0.9f, 0.9f, 0.9f, 1.0f };
  label->style.setPadding(10.0f, 4.0f);
  label->style.set(STYLE_MARGIN_TOP, -80.0f);
  addNode(label);
  //img->addChild(label);

  label2 = new UILabel("", 20);
  label2->style.color = { 1.0f, 1.0f, 0.0f, 1.0f };
  label2->style.setPadding(10.0f, 4.0f);
  label2->style.set(STYLE_MARGIN_TOP, -40.0f);
  addNode(label2);
}

Status::~Status()
{

}

void Status::onBeforeRender()
{
  Player* player = oak::PlayerResource::getLocalPlayer();
  Entity* ent = player->getAssignedEntity();
  if (ent != nullptr)
  {
    Unit* unit = ent->getComponent<Unit>();

    prop_hp = unit->getHealth();
    label->text = "HP:" + std::to_string(prop_hp) + "/" + std::to_string(unit->getMaxHealth());

    //Localization::strings[STRING_MANA]
    prop_mana = unit->getMana();
    label2->text = "MANA:" + std::to_string(prop_mana) + "/" + std::to_string(unit->getMaxMana());
  }
}
