#include "move_script.h"

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

  

  if (Input::isKeyDown(KeyCode::C))
  {
    glm::vec3 pt = Oakitus::camera->cursorToWorld2D();
    std::cout << "vp:" << Input::mousePos.x << "," << Input::mousePos.y << std::endl <<
      "rayWorld:" << pt.x << "," << pt.y << "," << pt.z << std::endl <<
      "entPos:" << entity->position.x << "," << entity->position.y << std::endl;

    entity->position = glm::vec3(pt.x, pt.y, 0);
  }


}