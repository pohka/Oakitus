
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
#include <oak/lua/lua_loader.h>

#define STB_IMAGE_IMPLEMENTATION
#include <oak/assets/stb_image.h>

#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>
#include <fstream>
#include <oak/debug.h>

using namespace oak;
using json = nlohmann::json;


void Oakitus::init()
{
  Time::init();
  Input::init();

  nlohmann::json config;
  std::ifstream i("../config.json");
  i >> config;
  if (config == nullptr)
  {
    //config not found
    LOG_ERROR << "config.json - file not found";
    return;
  }

  //no project name
  if (config["project"] == nullptr)
  {
    LOG_ERROR << "config.json - 'project' bust be defined";
    return;
  }

  //project name is not a string value
  if (config["project"].is_string() == false)
  {
    LOG_ERROR << "config.json - expected 'project' key to be string";
    return;
  }

  std::string projectName = config["project"];
  std::string projectPath = "../projects/" + projectName + "/";
  Resources::rootPath = projectPath + "resources/";

  Camera::init(
    glm::vec3(0.0f, 0.0f, 5.0f), //position
    glm::vec3(0.0f, 0.0f, -1.0f), //front
    glm::vec3(0.0f, 1.0f, 0.0f), //up
    90.0f, //field or view
    true
  );


  //validate config params
  uint  viewportW = 736,
    viewportH = 414,
    windowW = 1066,
    windowH = 600;

  uint vals[4] = {
    viewportW, 
    viewportH, 
    windowW,
    windowH
  };
  const unsigned int UINT_KEYS = 4;
  std::string keys[UINT_KEYS] = { "viewport_w", "viewport_h", "window_w", "window_h" };

  for (unsigned int i = 0; i < UINT_KEYS; i++)
  {
    std::string key = keys[i];
    if (config[key] != nullptr)
    {
      if (config[key].is_number_unsigned())
      {
        vals[i] = config[key];
      }
      else
      {
        LOG_WARNING << "config.json - expected unsigned integer for '" << keys[i] << "'";
      }
    }
  }

  bool isFullscreen = false;
  if (config["isFullscreen"] != nullptr)
  {
    if (config["isFullscreen"].is_boolean())
    {
      isFullscreen = config["isFullscreen"];
    }
    else
    {
      LOG_WARNING << "config.json - expected boolean for 'isFullscreen'";
    }
  }

  std::string title = projectName;
  if (config["title"] != nullptr)
  {
    if (config["title"].is_string())
    {
      title = config["title"];
    }
    else
    {
      LOG_WARNING << "config.json - expected string for 'isFullscreen'";
    }
  }
  
  Window::init(
    vals[0],
    vals[1],
    vals[2],
    vals[3],
    title.c_str(),
    isFullscreen
  );
  
  GLFWwindow* window = Window::getGLFWWindow();
  
  Resources::init();

  PlayerResource::addPlayer(new Player());

  //loads scripts/main.lua
  LuaLoader::init(projectPath);

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
    EntityManager::tickInstances(TICK_GROUP_LAST);
    EntityManager::drawInstances();
    EntityManager::debugDrawInstances();
    ion::UICanvas::render();

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
  glfwTerminate();
  return 0;
}
