
#include "oakitus.h"
#include "time.h"
#include "input.h"
#include "camera.h"
#include "entity.h"
#include <glm/glm.hpp>
#include "../debug.h"
#include "window.h"
#include "shader.h"
#include "resources.h"
#include "scene.h"
#include "texture.h"
#include "player_resource.h"
#include "../collision/collision.h"
#include "../oak_def.h"
#include "../ui/ui_canvas.h"
#include "../debug/debug_input.h"
#include "../meta/meta.h"

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
    debug::DebugInput::process();

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Entity::instantiateQueuedEnts();
    PlayerResource::executeAllCommands();
    Entity::updateInstances();
    Collision::resolveCollisions();
    Entity::lateUpdateInstances();
    Entity::drawInstances();
    Entity::debugDrawInstances();
    ion::UICanvas::render();

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
