#include "Key.h"

Key::Key(KeyCode code)
{
	this->code = code;
	this->isDown = false;
	this->lastIsDown = false;
}

Key::~Key() {}

void Key::setState(bool isDown)
{
	this->lastIsDown = this->isDown;
	this->isDown = isDown;
}

KeyCode Key::getCode()
{
	return this->code;
}
