#ifndef INPUT_H
#define INPUT_H

#include "key_buffer.h"
#include <GLFW/glfw3.h>
#include "key_code.h"
#include "point.h"
#include "types.h"

namespace oak
{
  ///<summary>Input states</summary>
  class Input
  {
    static KeyBuffer* keys[sizeof(glKeys)]; ///<summary>All of the tracked keys buffers</summary>

    public:
      
      static const uint KEY_COUNT = sizeof(glKeys); ///<summary>Total number of keys being tracked</summary>
      static Point mousePos; ///<summary>Cursor position in window coordinates</summary>

      ///<summary>Initalize Input</summary>
      static void init();

      ///<summary>Returns true if the key was pressed down this frame</summary>
      static bool isKeyDown(KeyCode code); //key just pressed down

      ///<summary>Returns true if this key is currently down</summary>
      static bool isKeyPressed(KeyCode code); //key current down state

      ///<summary>Returns true if key was released this frame</summary>
      static bool isKeyUp(KeyCode code);//key just released

      ///<summary>Process the input and update the buffers</summary>
      static void processInput(GLFWwindow* window);

      ///<summary>Set the captured cursor position for this frame</summary>
      static void setMouse(float x, float y);

    private:
      ///<summary>Returns the Key buffer with a maching code</summary>
      static KeyBuffer* getKeyBufferByCode(uint code);
  };
}

#endif
