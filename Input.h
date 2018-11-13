#ifndef INPUT_H
#define INPUT_H

#include "Key.h"
#include <GLFW/glfw3.h>
#include "KeyCode.h"

using namespace input;

class Input
{
public:

	static const unsigned int KEY_COUNT = sizeof(input::glKeys);
	static void init();
	static void setKeys(GLFWwindow* window);
	static bool isKeyDown(KeyCode code); //key just pressed down
	static bool isKeyUp(KeyCode code);//key just released
	static bool isKeyPressed(KeyCode code); //key current down state
private :
	static Key* getKeyByCode(unsigned int code);
	static Key* keys[KEY_COUNT];
};

#endif
