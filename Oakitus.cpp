#include "Oakitus.h"

GLWindow* Oakitus::glWindow = nullptr;
std::vector<Shader*> Oakitus::shaders;
std::vector<Entity*> Oakitus::entities;
IDGenerator* Oakitus::shaderIDGen = new IDGenerator();
Scene* Oakitus::curScene = nullptr;
unsigned int Oakitus::defaultShaderID;
std::queue<unsigned int> Oakitus::destroyEntIDQueue;
Camera* Oakitus::camera = nullptr;


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

void Oakitus::onUpdate()
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[i]->onUpdate();
	}
}

void Oakitus::onDraw()
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[i]->onDraw();
	}
}

void Oakitus::destroy(unsigned int entityID)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getID() == entityID)
		{
			Entity* ent = entities[i];
			entities.erase(entities.begin() + i);
			delete ent;
		}
	}
}

void Oakitus::setScene(Scene& scene)
{
	//unload and delete current scene
	if (curScene != nullptr) {
		curScene->onUnload();
		Scene* tmp = curScene;
		delete tmp;
	}
	//set and load new scene
	curScene = &scene;
	curScene->onLoad();
}

void Oakitus::deleteAllEnts()
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		Entity* tmp = entities[i];
		entities.erase(entities.begin() + i); //remove from vector
		i--;
		delete tmp;
	}
}

void Oakitus::deleteAllEnts(std::vector<int> exceptionIDs)
{
	bool isException = false;
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		isException = false;
		unsigned int entID = entities[i]->getID();
		for (unsigned int a = 0; a < exceptionIDs.size() && !isException; a++)
		{
			if (entID == exceptionIDs[a])
			{
				isException = true;
			}
		}
		if (!isException)
		{
			Entity* tmp = entities[i];
			entities.erase(entities.begin() + i); //remove from vector
			i--;
			delete tmp;
		}
	}
}

void Oakitus::destroyEntityByID(unsigned int entityID)
{
	destroyEntIDQueue.push(entityID);
}

void Oakitus::onDestroy()
{
	while(!destroyEntIDQueue.empty())
	{
		unsigned int id = destroyEntIDQueue.front();
		Entity* ent= nullptr;
		bool found = false;

		//find entity with matching id, then remove from vector
		for (unsigned int i = 0; i < entities.size() && !found; i++)
		{
			if (entities[i]->getID() == id)
			{
				ent = entities[i];
				entities.erase(entities.begin() + i);
				found = true;
			}
		}
		//call onDestroy and delete the object
		if (found)
		{
			ent->onDestroy();
			delete ent;
		}

		destroyEntIDQueue.pop();
	}
}
