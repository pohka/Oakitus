#ifndef INPUT_H
#define INPUT_H

#include "Key.h"
#include <GLFW/glfw3.h>
#include "KeyCode.h"
#include "Vector2.h"

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
	static void setMouse(float x, float y);
	static Vector2* mousePos;
private :
	static Key* getKeyByCode(unsigned int code);
	static Key* keys[KEY_COUNT];
	
};

#endif
