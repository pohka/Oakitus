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
		virtual void onUpdate();
		virtual void onDraw();
		Vector3* position;
		void addComponent(Component& component);
		void addScript(Script& script);
		unsigned int getID();
		virtual void onDestroy();
		void destroy();
	private : 
		unsigned int entityID;
		std::vector<Component*> components;
		std::vector<Script*> scripts;
		IDGenerator* idGen;
		
};

#endif