#include "input.h"

using namespace oak;


KeyBuffer* Input::keys[sizeof(glKeys)];
Point Input::mousePos(0, 0);


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
  for (uint i = 0; i < KEY_COUNT; i++)
  {
    int code = glKeys[i];
    keys[i] = new KeyBuffer((KeyCode)code);
  }
}

bool Input::isKeyDown(KeyCode code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown == true && key->lastIsDown == false;
}

bool Input::isKeyPressed(KeyCode code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown;
}

bool Input::isKeyUp(KeyCode code)
{
  KeyBuffer* key = Input::getKeyBufferByCode(code);
  return key->isDown == false && key->lastIsDown == true;
}

void Input::processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }

  for (uint i = 0; i < KEY_COUNT; i++)
  {
    int code = glKeys[i];
    bool isKeyDown = glfwGetKey(window, code) == GLFW_PRESS;
    keys[i]->setState(isKeyDown);
  }
}

void Input::setMouse(float x, float y)
{
  mousePos.x = x;
  mousePos.y = y;
}