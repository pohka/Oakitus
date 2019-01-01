
#include "oakitus.h"
#include "time.h"
#include "input.h"
#include "camera.h"
#include "entity.h"
#include <glm/glm.hpp>
#include <oak/debug.h>
#include "window.h"
#include "shader.h"
#include "resources.h"
#include "scene.h"
#include "texture.h"
#include "player_resource.h"
#include <oak/collision/collision.h>
#include <oak/oak_def.h>
#include <oak/ui/ui_canvas.h>
#include <oak/debug/debug_input.h>
#include <oak/meta/meta.h>
#include <oak/core/entity_manager.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <thread> 
#include <chrono> 


using namespace oak;


void Oakitus::init(uint viewportW, uint viewportH, uint windowW, uint windowH, bool isFullscreen)
{
  Time::init();
  Input::init();
  
  Meta::load();

  Camera::init(
    glm::vec3(0.0f, 0.0f, 5.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f, //field or view
    true
  );

  Window::init(viewportW, viewportH, windowW, windowH, "Oakitus", isFullscreen);
  GLFWwindow* window = Window::getGLFWWindow();
  
  Resources::init();

  //Shader *collisionShader = new Shader("collision");
  //Resources::addShader(*collisionShader);

  PlayerResource::addPlayer(new Player());
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
    Time::onTick();
    Input::processInput(window);
    debug::DebugInput::process();

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EntityManager::instantiateQueuedEnts();
    PlayerResource::executeAllCommands();
    EntityManager::tickInstances(TICK_GROUP_DEFAULT);
    Collision::resolveCollisions();
    EntityManager::tickInstances(TICK_GROUP_AFTER_PHYSICS);
    EntityManager::tickInstances(TICK_GROUP_LAST);
    EntityManager::drawInstances();
    EntityManager::debugDrawInstances();
    ion::UICanvas::render();

    if (Scene::isNextSceneSet())
    {
      Scene::swapScene();
    }
    else
    {
      EntityManager::destroyQueuedInstances();
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();

    Time::fpslimiter.sleep();
  }
  glfwTerminate();
  return 0;
}
