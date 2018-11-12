#include "Game.h"

#include "Oakitus.h"
#include "Sprite.h"
#include "Entity.h"

Oakitus* m_engine;


void Game::load(Oakitus* engine)
{
	m_engine = engine;
}

void Game::init()
{
	Entity* ent = new Entity();
	Sprite* s = new Sprite("face.png", 0, 0, 10, 10);
	ent->addComponent(*s);
	m_engine->entities.push_back(ent);
	
}

void Game::update()
{

}

void Game::draw()
{
	m_engine->entities[0]->draw(*m_engine->shaders[0]);
}