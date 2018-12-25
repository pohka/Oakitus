#include "input.h"

using namespace oak;


KeyBuffer* Input::keys[sizeof(glKeys)];
KeyBuffer* Input::mouseButtons[MOUSE_BUTTON_LAST];
Point Input::mousePos = { 0,0 };
Point Input::lastMousePos = { 0,0 };
bool Input::m_hasMouseMoved = false;


KeyBuffer* Input::getKeyBufferByCode(uint query)
{
  for (uint i = 0; i < KEY_COUNT; i++)
  {
    int code = glKeys[i];
    if (keys[i]->code == query)
    {
      return keys[i];
    }
  }
  return nullptr;
}

void Input::init()
{
  //keyboard buttons
  for (uint i = 0; i < KEY_COUNT; i++)
  {
    ushort code = glKeys[i];
    keys[i] = new KeyBuffer(code);
  }

  //mouse buttons
  for (uint i = 0; i < MOUSE_BUTTON_LAST; i++)
  {
    mouseButtons[i] = new KeyBuffer(i);
  }
}

bool Input::isKeyDown(ushort code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown == true && key->lastIsDown == false;
}

bool Input::isKeyPressed(ushort code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown;
}

bool Input::isKeyUp(ushort code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown == false && key->lastIsDown == true;
}

bool Input::isMouseButtonDown(uchar code)
{
  KeyBuffer* btn = mouseButtons[code];
  return btn->isDown == true && btn->lastIsDown == false;
}

bool Input::isMouseButtonPressed(uchar code)
{
  KeyBuffer* btn = mouseButtons[code];
  return btn->isDown;
}

bool Input::isMouseButtonUp(uchar code)
{
  KeyBuffer* btn = mouseButtons[code];
  return btn->isDown == false && btn->lastIsDown == true;
}

void Input::processInput(GLFWwindow* window)
{
  //keyboard keys
  for (uint i = 0; i < KEY_COUNT; i++)
  {
    int code = glKeys[i];
    bool isKeyDown = glfwGetKey(window, code) == GLFW_PRESS;
    keys[i]->setState(isKeyDown);
  }

  //mouse buttons
  for (uint i = 0; i < MOUSE_BUTTON_LAST; i++)
  {
    bool isBtnDown = glfwGetMouseButton(window, i);
    mouseButtons[i]->setState(isBtnDown);
  }
}

void Input::setMouse(float x, float y)
{
  m_hasMouseMoved = (mousePos.x != x || mousePos.y != y);

  lastMousePos.x = mousePos.x;
  lastMousePos.y = mousePos.y;
  mousePos.x = x;
  mousePos.y = y;
}

Point Input::getLastMousePt()
{
  return lastMousePos;
}

bool Input::hasMouseMoved()
{
  return m_hasMouseMoved;
}