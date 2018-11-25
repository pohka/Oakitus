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
  initOak();
  Window::init(SCR_WIDTH, SCR_HEIGHT, "Oakitus");
  GLFWwindow* window = Window::getGLFWWindow();
  glfwSetCursorPosCallback(window, cursorMoved);

  
  // build and compile our shader zprogram
  // ------------------------------------
  Shader *shader = new Shader("default", "default.vs", "default.fs");
  Resources::addShader(*shader);
  Resources::defaultShaderID = shader->getID();
  std::cout << "shader default: " << shader->getID() << std::endl;
  shader->use();

  //set projection matrix
  float aspect = (float)Window::getAspectRatio();
  glm::mat4 projection = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
  shader->setMat4("projection", projection);

  Resources::addTexture("default.png");


  Game::load();

  //console.log("")
  //XMLNode* child = root.getChildNodes()[0];
 // std::cout << "xml:" << child->getContent() << std::endl;

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    Time::update();
    Input::processInput(window);

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Oakitus::updateEnts();
    Oakitus::drawEnts();

    if (Store::isNewSceneSet())
    {
      Store::onSceneChange();
    }

    Oakitus::destroyQueue();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();

    //sleep to limit fps
    float minDelta = Time::getMinDeltaTime();
    if (Time::deltaTime < minDelta)
    {
      int sleepTime = (int)((minDelta - Time::deltaTime) * 1000.f);
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

void cursorMoved(GLFWwindow* window, double xpos, double ypos)
{
  // invert y-coordinate
  Input::setMouse((float)xpos, (float)Window::getHeight() - (float)ypos);
}



