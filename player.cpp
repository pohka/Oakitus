#include "player.h"

using namespace game;

Player::Player()
{
  assignedUnit = nullptr;
}

Player::~Player()
{
  if (assignedUnit != nullptr)
  {
    delete assignedUnit;
  }
}

void Player::setAssignedUnit(Unit& unit)
{
  assignedUnit = &unit;
}

Unit& Player::getAssignedUnit()
{
  return *assignedUnit;
}