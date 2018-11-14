#include "MoveScript.h"

#include "Input.h"
#include <iostream>
#include "Entity.h"
#include "Time.h"
#include "Oakitus.h"

MoveScript::MoveScript() {}
MoveScript::~MoveScript() {}

void MoveScript::onUpdate()
{
	float speed = 1.0f * Time::deltaTime;
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

	if (Input::isKeyDown(input::KeyCode::BACKSPACE))
	{
		entity->destroy();
	}
}