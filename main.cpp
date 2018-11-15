#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Shader.h"
#include "Camera.h"


#include <iostream>

#include "Sprite.h"

#include "GLWindow.h"

#include "Oakitus.h"
#include "Game.h"
#include "Input.h"
#include "Time.h"

#include "SampleScene.h"

using namespace oak;


void processInput(GLFWwindow *window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  Time::init();
  Input::init();
  Oakitus::glWindow = new GLWindow(SCR_WIDTH, SCR_HEIGHT, "Oakitus");
  GLFWwindow* window = Oakitus::glWindow->getGLFWWindow();
  glfwSetCursorPosCallback(window, cursor_position_callback);

  Oakitus::camera = new Camera(
    glm::vec3(0.0f, 0.0f, 3.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f //field or view
  );

  
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //// render container
    shader->use();


    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(
      glm::radians(Oakitus::camera->fov), 
      (float)SCR_WIDTH / (float)SCR_HEIGHT, 
      0.1f, 
      100.0f
    );
    shader->setMat4("projection", projection);
    

    // camera/view transformation
    glm::mat4 view = glm::lookAt(
      Oakitus::camera->position, 
      Oakitus::camera->position + Oakitus::camera->front, 
      Oakitus::camera->up
    );
    shader->setMat4("view", view);


    if (Input::isKeyDown(KeyCode::R))
    {
      std::cout << "r is down " << std::endl;
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



