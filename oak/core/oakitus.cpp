
#include "oakitus.h"
#include "time.h"
#include "input.h"
#include "camera.h"
#include "entity.h"
#include <glm/glm.hpp>
#include "debug.h"
#include "window.h"
#include "shader.h"
#include "resources.h"
#include "scene.h"
#include "texture.h"
#include "player_resource.h"
#include "../components/collision.h"
#include "../oak_def.h"
#include "../fallback.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <thread> 
#include <chrono> 


using namespace oak;


void Oakitus::init()
{
  Time::init();
  Input::init();

  Camera::init(
    glm::vec3(0.0f, 0.0f, 5.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f, //field or view
    true
  );

  Window::init(SCR_WIDTH, SCR_HEIGHT, SCR_WIDTH, SCR_HEIGHT, "Oakitus");
  GLFWwindow* window = Window::getGLFWWindow();
  
  Fallback::init();
  Resources::addTexture("box.png");
  Resources::addTexture("circle.png");

  //Shader *collisionShader = new Shader("collision");
  //Resources::addShader(*collisionShader);


  Oakitus::load();
  loop();
}

int Oakitus::loop()
{
  GLFWwindow* window = Window::getGLFWWindow();
  // render loop
  // -----------
  while (!glfwWindowShouldClose(window))
  {
    Time::update();
    Input::processInput(window);

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Entity::instantiateQueuedEnts();

    PlayerResource::executeAllCommands();
    Entity::updateInstances();
    Fallback::update();
    Collision::resolveCollisions();
    Entity::drawInstances();
    Fallback::draw();
    Entity::debugDrawInstances();

    

    if (Scene::isNextSceneSet())
    {
      Scene::swapScene();
    }
    else
    {
      Entity::destroyQueuedInstances();
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();

    //sleep to limit fps
    float minDelta = Time::getMinDeltaTime();
    if (Time::deltaTime() < minDelta)
    {
      int sleepTime = (int)((minDelta - Time::deltaTime()) * 1000.f);
      std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    }
  }
  glfwTerminate();
  return 0;
}
