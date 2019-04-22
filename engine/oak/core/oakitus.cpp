
#include "oakitus.h"
#include "time.h"
#include <oak/input/input.h>
#include <oak/scene/camera.h>
#include <oak/ecs/entity.h>
#include <glm/glm.hpp>
#include <oak/window/window.h>
#include <oak/assets/shader.h>
#include "resources.h"
#include <oak/scene/scene_manager.h>
#include <oak/assets/texture.h>
#include <oak/player/player_resource.h>
#include <oak/collision/collision.h>
#include <oak/oak_def.h>
#include <oak/ui/ui_canvas.h>
#include <oak/debug/debug_input.h>
#include <oak/ecs/entity_manager.h>
#include <oak/time/time.h>
#include <oak/lua/lua_s.h>
#include <oak/core/config.h>
#include <oak/meta/meta_data.h>
#include <oak/ability/combat.h>

#define STB_IMAGE_IMPLEMENTATION
#include <oak/assets/stb_image.h>

#include <thread>
#include <chrono>

using namespace oak;
using json = nlohmann::json;


void Oakitus::init()
{
  Time::init();
  Input::init();

  Config::load();

  std::string projectName = Config::getString("project", "default");
  std::string projectPath = "../projects/" + projectName + "/";
  MetaData::projectPath = projectPath;
  Resources::rootPath = projectPath + "resources/";

  Camera::init(
    glm::vec3(0.0f, 0.0f, 5.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f, //field or view
    true
  );


  //validate config params
  uint  
    viewportW = Config::getUInt("viewport_w", 736),
    viewportH = Config::getUInt("viewport_h", 414),
    windowW = Config::getUInt("window_w", 1066),
    windowH = Config::getUInt("window_h", 600);

  std::string title = Config::getString("title", "Oakitus");
  bool isFullscreen = Config::getBool("isFullscreen", false);

  Window::init(
    viewportW,
    viewportH,
    windowW,
    windowH,
    title.c_str(),
    isFullscreen
  );
  
  GLFWwindow* window = Window::getGLFWWindow();
  
  Resources::init();

  PlayerResource::addPlayer(new Player());

  Combat::init();

  //loads scripts/main.lua
  LuaS::init();

  //Oakitus::load();
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

#ifdef DEBUG_MODE
    debug::DebugInput::process();
#endif

    glClearColor(0.1f, 0.25f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EntityManager::instantiateQueuedEnts();
    PlayerResource::tickAllCommands();
    EntityManager::tickInstances(TICK_GROUP_DEFAULT);
    Collision::resolveCollisions();
    EntityManager::tickInstances(TICK_GROUP_AFTER_PHYSICS);
    Combat::onTick();
    EntityManager::tickInstances(TICK_GROUP_LAST);
    EntityManager::drawInstances();

#ifdef DEBUG_MODE
    EntityManager::debugDrawInstances();
#endif
    
    ion::UICanvas::render();

    EntityManager::checkRequestedDestroys();

    if (SceneManager::isNextSceneSet())
    {
      SceneManager::swapScene();
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
  LuaS::close();
  glfwTerminate();
  return 0;
}
