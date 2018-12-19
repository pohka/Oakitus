#include "inventory.h"
#include <debug.h>

using namespace game;

Inventory::Inventory(uint ownerID)
{
  LOG << "inventroy constructor";
  this->ownerID = ownerID;
  
}

Inventory::~Inventory()
{

}

void Inventory::addItem(Item* item)
{
  items.push_back(item);

  LOG << "added item to inventory";
  //temp for testing
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
    //unequip existing
    if (slots[item->slot] != nullptr)
    {
      slots[item->slot]->isEquiped = false;
      slots[item->slot]->onUnEquip();
    }

    slots.insert(item->slot, item);
    item->ownerID = ownerID;
    item->isEquiped = true;
    item->onEquip();
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
    if (slots[slotID] != nullptr)
    {
      slots[slotID]->isEquiped = false;
      slots[slotID]->onUnEquip();
    }
    slots.insert(slotID, nullptr);
  }
  //todo remove item modifer to unit, e.g. onItemUnEquiped()

}

std::vector<Item*>& Inventory::getAllItems()
{
  return items;
}