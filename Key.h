#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "KeyCode.h"

using namespace input;

class Key
{
public:

	friend class Input;
	Key(KeyCode code);
	~Key();
	KeyCode getCode();
	
	
private:
	KeyCode code;
	void setState(bool isDown);
	bool isDown;
	bool lastIsDown;
};

#endif