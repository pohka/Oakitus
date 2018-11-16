#include "oak/init.h"

#include <iostream>

#include "game.h"
#include "sample_scene.h"

//#include <glm/gtc/matrix_transform.hpp>


using namespace oak;
using namespace game;


void processInput(GLFWwindow *window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 540;

int main()
{
  initOak();
  Oakitus::glWindow = new GLWindow(SCR_WIDTH, SCR_HEIGHT, "Oakitus");
  GLFWwindow* window = Oakitus::glWindow->getGLFWWindow();
  glfwSetCursorPosCallback(window, cursor_position_callback);

  
  // build and compile our shader zprogram
  // ------------------------------------
  Shader *shader = new Shader("default", "sample_texture.vs", "sample_texture.fs");
  Oakitus::addShader(*shader);
  Oakitus::defaultShaderID = shader->getID();

  Game::load();

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    Time::calcDeltaTime();

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //// render container
    
    shader->use();

    float aspect = 960.0f / 540.0f;

    glm::mat4 projection = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
    shader->setMat4("projection", projection);

    if (Input::isKeyDown(KeyCode::R))
    {
      std::cout << "refreshed scene" << std::endl;
      Oakitus::setScene(*new SampleScene());
    }

    Oakitus::onUpdate();
    Oakitus::onDraw();
    Oakitus::onDestroy();

    

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

void update()
{

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  Input::setKeys(window);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  // invert y-coordinate
  //todo: screen height should use current viewport height as the window can be resized
  Input::setMouse((float)xpos, (float)SCR_HEIGHT - (float)ypos);
}



