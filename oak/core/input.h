#ifndef INPUT_H
#define INPUT_H

#include "key.h"
#include <GLFW/glfw3.h>
#include "key_code.h"
#include "point.h"
#include "types.h"

namespace oak
{
  class Input
  {
    static Key* keys[sizeof(glKeys)];

    public:
      static const uint KEY_COUNT = sizeof(glKeys);
      static Point mousePos;

      static void init();
      static bool isKeyDown(KeyCode code); //key just pressed down
      static bool isKeyPressed(KeyCode code); //key current down state
      static bool isKeyUp(KeyCode code);//key just released
      static void setKeys(GLFWwindow* window);
      static void setMouse(float x, float y);

    private:
      static Key* getKeyByCode(uint code);
  };
}

#endif
