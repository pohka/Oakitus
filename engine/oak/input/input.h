#ifndef INPUT_H
#define INPUT_H

#include "key_buffer.h"
#include <GLFW/glfw3.h>
#include "key_codes.h"
#include "point.h"
#include <oak/core/types.h>

namespace oak
{
  ///<summary>Input states</summary>
  class Input
  {
    static KeyBuffer* keys[sizeof(glKeys)]; ///<summary>All of the tracked keys buffers</summary>
    static KeyBuffer* mouseButtons[MOUSE_BUTTON_LAST]; ///<summary>All of the tracked keys buffers</summary>
    static Point lastMousePos;
    static bool m_hasMouseMoved;

    public:
      
      static const uint KEY_COUNT = sizeof(glKeys); ///<summary>Total number of keys being tracked</summary>
      static Point mousePos; ///<summary>Cursor position in window coordinates</summary>
      

      ///<summary>Initalize Input</summary>
      static void init();

      ///<summary>Returns true if the key was pressed down this frame</summary>
      static bool isKeyDown(ushort code); //key just pressed down

      ///<summary>Returns true if this key is currently down</summary>
      static bool isKeyPressed(ushort code); //key current down state

      ///<summary>Returns true if key was released this frame</summary>
      static bool isKeyUp(ushort code);//key just released

      static bool isMouseButtonDown(uchar code); 
      static bool isMouseButtonPressed(uchar code);
      static bool isMouseButtonUp(uchar code);
      static Point getLastMousePt();
      static bool hasMouseMoved();

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
