#include "input.h"

using namespace oak;

Key* Input::keys[sizeof(glKeys)];
Vector2* Input::mousePos = new Vector2(0, 0);


Key* Input::getKeyByCode(uint query)
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
    keys[i] = new Key((KeyCode)code);
  }
}

bool Input::isKeyDown(KeyCode code)
{
  Key* key = Input::getKeyByCode(code);
  return key->isDown == true && key->lastIsDown == false;
}

bool Input::isKeyPressed(KeyCode code)
{
  Key* key = Input::getKeyByCode(code);
  return key->isDown;
}

bool Input::isKeyUp(KeyCode code)
{
  Key* key = Input::getKeyByCode(code);
  return key->isDown == false && key->lastIsDown == true;
}

void Input::setKeys(GLFWwindow* window)
{
  for (uint i = 0; i < KEY_COUNT; i++)
  {
    int code = glKeys[i];
    bool isKeyDown = glfwGetKey(window, code) == GLFW_PRESS;
    keys[i]->setState(isKeyDown);
  }
}

void Input::setMouse(float x, float y)
{
  mousePos->x = x;
  mousePos->y = y;
}