#include "MoveScript.h"

#include "Input.h"
#include <iostream>
#include "Entity.h"

MoveScript::MoveScript() {}
MoveScript::~MoveScript() {}

void MoveScript::update(Entity* ent)
{
	float speed = 0.0001f;
	if (Input::isKeyPressed(input::KeyCode::A))
	{
		this->entity->position->x -= speed;
	}
	if (Input::isKeyPressed(input::KeyCode::S))
	{
		this->entity->position->y -= speed;
	}
	if (Input::isKeyPressed(input::KeyCode::D))
	{
		this->entity->position->x += speed;
	}
	if (Input::isKeyPressed(input::KeyCode::W))
	{
		this->entity->position->y += speed;
	}
}