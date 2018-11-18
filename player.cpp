#include "player.h"
#include "oak/oak.h"
#include "move_script.h"

using namespace oak;
using namespace game;

Player::Player()
{
  name = "player";
  Shader* shader = Resources::findShaderByName("default");
  uint shaderID = shader->getID();
  Sprite* s = new Sprite("face.png", 0, 0, 1000, 1000, 200, 200, shaderID);
  addComponent(*s);
  Script* move = new MoveScript();
  addScript(*move);
}

Player::~Player()
{

}