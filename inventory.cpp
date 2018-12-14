#include "inventory.h"
#include <debug.h>

using namespace game;

Inventory::Inventory()
{
  LOG << "inventroy constructor";

  
}

Inventory::~Inventory()
{

}

void Inventory::addItem(Item* item)
{
  items.push_back(item);

  LOG << "inserting item to slots";
  slots.insert(ITEM_SLOT_ARMOR, item);
 // slots.insert(ITEM_SLOT_WEAPON , item);
 // Item* armorItem = slots.at(ITEM_SLOT_ARMOR);
  LOG << "armorItem:" << (slots[ITEM_SLOT_ARMOR] != nullptr);

  //slots.remove(ITEM_SLOT_ARMOR);
  LOG << "armorItem:" << (slots.at(ITEM_SLOT_ARMOR) != nullptr);
  slots.insert(ITEM_SLOT_WEAPON, item);

  LOG << "ITEMS::---------";
  for (auto it = slots.begin(); slots.end(); slots.next())
  {
    LOG << "KV:" << it->node->key << ":" << it->node->value->price;
  }


}

Item* Inventory::getItem(uint itemID)
{
  for (uint i = 0; i < items.size(); i++)
  {
    if (items[i]->getItemID() == itemID)
    {
      return items[i];
    }
  }

  LOG_WARNING << "Item not found with id:" << itemID;

  return nullptr;
}

void Inventory::equipItem(uint itemID)
{
  //todo: add item modifier to unit
}

void Inventory::unEquipItem(uint itemID)
{
  //todo remove item modifer to unit
}