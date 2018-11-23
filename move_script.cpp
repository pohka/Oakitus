#include "move_script.h"
#include "sample_scene.h"

using namespace oak;
using namespace game;

MoveScript::MoveScript() {}
MoveScript::~MoveScript() {}

void MoveScript::onUpdate()
{
  float speed = 800.0f * Time::deltaTime;
  if (Input::isKeyPressed(KeyCode::A))
  {
    this->entity->position.x -= speed;
  }
  if (Input::isKeyPressed(KeyCode::S))
  {
    this->entity->position.y -= speed;
  }
  if (Input::isKeyPressed(KeyCode::D))
  {
    this->entity->position.x += speed;
  }
  if (Input::isKeyPressed(KeyCode::W))
  {
    this->entity->position.y += speed;
  }

  if (Input::isKeyDown(KeyCode::BACKSPACE))
  {
    entity->destroy();
  }

  if (Input::isKeyPressed(KeyCode::UP))
  {
    Store::camera->position.y += speed;
  }
  if (Input::isKeyPressed(KeyCode::DOWN))
  {
    Store::camera->position.y -= 1.0f * speed;
  }
  if (Input::isKeyPressed(KeyCode::LEFT))
  {
    Store::camera->position.x -= speed;
  }
  if (Input::isKeyPressed(KeyCode::RIGHT))
  {
    Store::camera->position.x += speed;
  }

  if (Input::isKeyDown(KeyCode::R))
  {
    std::cout << "refreshed scene" << std::endl;
   // Store::setScene(*new SampleScene());
    Store::reloadScene();
  }

  if (Input::isKeyDown(KeyCode::F))
  {
    std::cout << "FPS:" << Time::getFPS() << std::endl;
  }

  if (Input::isKeyDown(KeyCode::C))
  {
    glm::vec3 pt = Store::camera->cursorToWorld2D();
    std::cout << "vp:" << Input::mousePos.x << "," << Input::mousePos.y << std::endl <<
      "rayWorld:" << pt.x << "," << pt.y << "," << pt.z << std::endl <<
      "entPos:" << entity->position.x << "," << entity->position.y << std::endl;

    entity->position = glm::vec3(pt.x, pt.y, 0);
  }

  if (Input::isKeyDown(I))
  {
    if (Store::findEntityByName("player") != nullptr)
    {
      std::cout << "found player" << std::endl;
    }
  }
}