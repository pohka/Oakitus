#ifndef ENTITY_H
#define ENTITY_H

#include "Script.h"
#include "Component.h"

#include <vector>
#include "Vector3.h"
#include "IDGenerator.h"


class Entity 
{
	unsigned int entityID;
	std::vector<Component*> components;
	std::vector<Script*> scripts;
	IDGenerator* idGen;

	public :
		Vector3* position;

		Entity();
		~Entity();
		void addComponent(Component& component);
		void addScript(Script& script);
		void destroy();
		unsigned int getID();
		virtual void onDestroy();
		virtual void onDraw();
		virtual void onUpdate();
		
};

#endif