#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "key_buffer.h"
#include <GLFW/glfw3.h>
#include "key_codes.h"
#include "point.h"
#include <oak/core/types.h>

namespace oak
{
  //Input states
  class Input
  {
    static KeyBuffer* keys[sizeof(glKeys)]; //All of the tracked keys buffers
    static KeyBuffer* mouseButtons[MOUSE_BUTTON_LAST]; //All of the tracked keys buffers
    static Point lastMousePos;
    static bool m_hasMouseMoved;

    public:
      
      static const uint KEY_COUNT = sizeof(glKeys); //Total number of keys being tracked
      static Point mousePos; //Cursor position in window coordinates
      

      //Initalize Input
      static void init();

      //Returns true if the key was pressed down this frame
      static bool isKeyDown(ushort code); //key just pressed down

      //Returns true if this key is currently down
      static bool isKeyPressed(ushort code); //key current down state

      //Returns true if key was released this frame
      static bool isKeyUp(ushort code);//key just released

      static bool isMouseButtonDown(uchar code); 
      static bool isMouseButtonPressed(uchar code);
      static bool isMouseButtonUp(uchar code);
      static Point getLastMousePt();
      static bool hasMouseMoved();

      //Process the input and update the buffers
      static void processInput(GLFWwindow* window);

      //Set the captured cursor position for this frame
      static void setMouse(float x, float y);

    private:
      //Returns the Key buffer with a maching code
      static KeyBuffer* getKeyBufferByCode(uint code);
  };
}

#endif
