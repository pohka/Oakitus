#ifndef COMPONENT_H
#define COMPONENT_H

#include "Shader.h"

class Entity;

class Component
{
	public:
		Component();
		virtual ~Component();
		static unsigned int getNextID();
		virtual void draw();
		Entity* entity;
	private:
		unsigned int componentID;
		
};

#endif