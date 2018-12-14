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

  equipItem(item);
  //slots.insert(ITEM_SLOT_ARMOR, item);
  //slots.insert(ITEM_SLOT_WEAPON, item);

  //LOG << "ITEMS::---------";
  //for (auto it = slots.begin(); slots.end(); slots.next())
  //{
  //  LOG << "KV:" << it->node->key << ":" << it->node->value->price;
  //}
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

void Inventory::equipItem(Item* item)
{
  if(item->slot != ITEM_SLOT_NONE)
  {
    slots.insert(item->slot, item);
  }
  else
  {
    //consumable
  }
  
  //todo: add item modifier to unit, e.g. onItemEquiped()
}

void Inventory::unEquipItem(uchar slotID)
{
  if (slotID != ITEM_SLOT_NONE)
  {
    slots.insert(slotID, nullptr);
  }
  //todo remove item modifer to unit, e.g. onItemUnEquiped()

}