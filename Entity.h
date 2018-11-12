#ifndef ENTITY_H
#define ENTITY_H

#include "Component.h"
#include <vector>
#include "Vector3.h"

class Entity 
{
	public :
		Entity();
		~Entity();
		static unsigned int getNextID();
		void draw(Shader& shader);
		Vector3* position;
		void addComponent(Component& component);
	private : 
		unsigned int entityID;
		std::vector<Component*> components;
};

#endif