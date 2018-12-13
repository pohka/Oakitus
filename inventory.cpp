#include "inventory.h"
#include <debug.h>

using namespace game;

Inventory::Inventory()
{

}

Inventory::~Inventory()
{

}

void Inventory::addItem(Item* item)
{
  items.push_back(item);
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