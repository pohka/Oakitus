#include "Game.h"

#include "Oakitus.h"
#include "Sprite.h"
#include "Entity.h"
#include "MoveScript.h"


void Game::load()
{
	
}

void Game::init()
{
	Entity* ent = new Entity();
	Sprite* s = new Sprite("face.png", 0, 0, 10, 10, NULL);
	ent->addComponent(*s);
	Script* move = new MoveScript();
	ent->addScript(*move);
	//Oakitus::destroy(ent->getID());

}