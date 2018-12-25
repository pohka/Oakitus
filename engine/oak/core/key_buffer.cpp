#include "key_buffer.h"

using namespace oak;

KeyBuffer::KeyBuffer(ushort code)
{
  this->code = code;
  this->isDown = false;
  this->lastIsDown = false;
}

KeyBuffer::~KeyBuffer() {}

ushort KeyBuffer::getCode() const
{
  return this->code;
}

void KeyBuffer::setState(bool isDown)
{
  this->lastIsDown = this->isDown;
  this->isDown = isDown;
}


