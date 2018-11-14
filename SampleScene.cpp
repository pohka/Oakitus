#include "SampleScene.h"
#include "Entity.h"
#include "Sprite.h"
#include "MoveScript.h"
#include "Oakitus.h"

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

void SampleScene::onLoad()
{
	Entity* ent = new Entity();
	Sprite* s = new Sprite("face.png", 0, 500, 700, 500, NULL);
	ent->addComponent(*s);
	Script* move = new MoveScript();
	ent->addScript(*move);
}

void SampleScene::onUnload()
{
	Oakitus::deleteAllEnts();
}