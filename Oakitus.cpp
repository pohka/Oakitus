#include "Oakitus.h"

GLWindow* Oakitus::glWindow = nullptr;
std::vector<Shader*> Oakitus::shaders;
std::vector<Entity*> Oakitus::entities;
IDGenerator* Oakitus::shaderIDGen = new IDGenerator();
unsigned int Oakitus::defaultShaderID;


Shader* Oakitus::getShaderByID(unsigned int id)
{
	return shaders[0];
}

void Oakitus::addShader(Shader& shader)
{
	shaders.push_back(&shader);
}

Entity* Oakitus::findEntityByID(unsigned int id)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == id)
		{
			return entities[i];
		}
	}

	return nullptr;
}


void Oakitus::addEntity(Entity& entity)
{
	entities.push_back(&entity);
}

Shader* Oakitus::findShaderByName(std::string name)
{
	for (unsigned int i = 0; i < shaders.size(); i++)
	{
		if (shaders[i]->getName().compare(name) == 0)
		{
			return shaders[i];
		}
	}
	return nullptr;
}