#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <vector>
#include "Vector3.h"
#include "IDGenerator.h"

class Entity 
{
	public :
		Entity();
		~Entity();
		void draw(Shader& shader);
		Vector3* position;
		void addComponent(Component& component);
		unsigned int getID();
	private : 
		unsigned int entityID;
		std::vector<Component*> components;
		IDGenerator* idGen;
		
};

#endif