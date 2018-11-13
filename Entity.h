#ifndef ENTITY_H
#define ENTITY_H

#include "Script.h"
#include "Component.h"

#include <vector>
#include "Vector3.h"
#include "IDGenerator.h"


class Entity 
{
	public :
		Entity();
		~Entity();
		void update();
		void draw();
		Vector3* position;
		void addComponent(Component& component);
		void addScript(Script& script);
		unsigned int getID();
	private : 
		unsigned int entityID;
		std::vector<Component*> components;
		std::vector<Script*> scripts;
		IDGenerator* idGen;
		
};

#endif