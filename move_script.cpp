#include "move_script.h"
#include "sample_scene.h"

using namespace oak;
using namespace game;

MoveScript::MoveScript() {}
MoveScript::~MoveScript() {}

void MoveScript::onUpdate()
{
  float speed = 1.0f * Time::deltaTime;
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
    Oakitus::camera->position.y += speed;
  }
  if (Input::isKeyPressed(KeyCode::DOWN))
  {
    Oakitus::camera->position.y -= 1.0f * speed;
  }
  if (Input::isKeyPressed(KeyCode::LEFT))
  {
    Oakitus::camera->position.x -= speed;
  }
  if (Input::isKeyPressed(KeyCode::RIGHT))
  {
    Oakitus::camera->position.x += speed;
  }

  if (Input::isKeyDown(KeyCode::R))
  {
    std::cout << "refreshed scene" << std::endl;
    Oakitus::setScene(*new SampleScene());
  }

  if (Input::isKeyDown(KeyCode::F))
  {
    std::cout << "FPS:" << Time::getFPS() << std::endl;
  }

  if (Input::isKeyDown(KeyCode::C))
  {
    glm::vec3 pt = Oakitus::camera->cursorToWorld2D();
    std::cout << "vp:" << Input::mousePos.x << "," << Input::mousePos.y << std::endl <<
      "rayWorld:" << pt.x << "," << pt.y << "," << pt.z << std::endl <<
      "entPos:" << entity->position.x << "," << entity->position.y << std::endl;

    entity->position = glm::vec3(pt.x, pt.y, 0);
  }

}