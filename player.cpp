#include "player.h"

using namespace oak;
using namespace game;

IDGenerator Player::idGen = IDGenerator();


Player::Player()
{
  playerID = idGen.nextID();
  assignedUnit = nullptr;
}

Player::~Player()
{

}

uint Player::getID()
{
  return playerID;
}

void Player::setAssignedUnit(Unit& unit)
{
  assignedUnit = &unit;
}

Unit& Player::getAssignedUnit()
{
  return *assignedUnit;
}
