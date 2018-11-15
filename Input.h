#ifndef INPUT_H
#define INPUT_H

#include "Key.h"
#include <GLFW/glfw3.h>
#include "KeyCode.h"
#include "Vector2.h"

namespace oak
{
  class Input
  {
    static Key* keys[sizeof(glKeys)];

    public:
      static const unsigned int KEY_COUNT = sizeof(glKeys);
      static Vector2* mousePos;

      static void init();
      static bool isKeyDown(KeyCode code); //key just pressed down
      static bool isKeyPressed(KeyCode code); //key current down state
      static bool isKeyUp(KeyCode code);//key just released
      static void setKeys(GLFWwindow* window);
      static void setMouse(float x, float y);

    private:
      static Key* getKeyByCode(unsigned int code);
  };
}

#endif
