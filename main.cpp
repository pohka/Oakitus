#include "oak/init.h"

#include <iostream>

#include "oak/game.h"
#include <thread> 
#include <chrono> 
#include "oak/core/oakitus.h"

using namespace oak;
using namespace game;


void cursorMoved(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1440;
const unsigned int SCR_HEIGHT = 810;


int main()
{
  Oakitus::init();
  Oakitus::loop();
  return 0;
}



