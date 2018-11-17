#include "oak/init.h"

#include <iostream>

#include "game.h"
#include "sample_scene.h"
#include <thread> 
#include <chrono> 

using namespace oak;
using namespace game;


void processInput(GLFWwindow *window);
void cursorMoved(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;


int main()
{
  initOak();
  Oakitus::glWindow = new GLWindow(SCR_WIDTH, SCR_HEIGHT, "Oakitus");
  GLFWwindow* window = Oakitus::glWindow->getGLFWWindow();
  glfwSetCursorPosCallback(window, cursorMoved);

  
  // build and compile our shader zprogram
  // ------------------------------------
  Shader *shader = new Shader("default", "sample_texture.vs", "sample_texture.fs");
  Resources::addShader(*shader);
  Resources::defaultShaderID = shader->getID();
  std::cout << "shader default: " << shader->getID() << std::endl;
  shader->use();

  Resources::addTexture("default.png");
  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");

  Game::load();

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    Time::update();
    Input::processInput(window);

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set projection matrix
    float aspect = Oakitus::glWindow->getAspectRatio();
    glm::mat4 projection = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    shader->setMat4("projection", projection);

    Oakitus::onUpdate();
    Oakitus::onDraw();
    Oakitus::onDestroy();

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
  //todo: screen height should use current viewport height as the window can be resized
  Input::setMouse((float)xpos, (float)SCR_HEIGHT - (float)ypos);
}



