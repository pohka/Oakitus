#include "Oakitus.h"

GLWindow* Oakitus::glWindow = nullptr;
std::vector<Shader*> Oakitus::shaders;
std::vector<Entity*> Oakitus::entities;
IDGenerator* Oakitus::shaderIDGen = new IDGenerator();


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
