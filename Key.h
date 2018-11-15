#ifndef KEYOBJ_H
#define KEYOBJ_H
#include "KeyCode.h"

using namespace input;

class Key
{
	KeyCode code;
	bool isDown;
	bool lastIsDown;

	public:
		friend class Input;
		Key(KeyCode code);
		~Key();
		KeyCode getCode();
	
	
	private:
		void setState(bool isDown);
	
};

#endif