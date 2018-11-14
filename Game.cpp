#include "Game.h"

#include "Oakitus.h"
#include "Sprite.h"
#include "Entity.h"
#include "MoveScript.h"
#include "SampleScene.h"


void Game::load()
{
	Scene* defaultScene = new SampleScene();
	Oakitus::setScene(*defaultScene);
}