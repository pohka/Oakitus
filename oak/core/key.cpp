#include "key.h"

using namespace oak;

Key::Key(KeyCode code)
{
  this->code = code;
  this->isDown = false;
  this->lastIsDown = false;
}

Key::~Key() {}

KeyCode Key::getCode()
{
  return this->code;
}

void Key::setState(bool isDown)
{
  this->lastIsDown = this->isDown;
  this->isDown = isDown;
}


