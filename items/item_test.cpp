#include "item_test.h"
#include <debug.h>
#include <oak.h>
#include "../unit.h"
#include "../abilitys/modifiers/modifier_test.h"

using namespace game;

ItemTest::ItemTest()
{
  slot = ITEM_SLOT_ARMOR;
}

void ItemTest::onEquip()
{
  LOG << "equiped test item";
  Unit* owner = static_cast<Unit*>(oak::Entity::findEntityByID(ownerID));
  if (owner != nullptr)
  {
    owner->addModifier(ownerID, new ModifierTest());
  }
  else
  {
    LOG << "OWNER NOT FOUND";
  }
}

void ItemTest::onUnEquip()
{

}