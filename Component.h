#ifndef COMPONENT_H
#define COMPONENT_H

#include "Shader.h"

class Component
{
	public:
		Component();
		virtual ~Component();
		static unsigned int getNextID();
		virtual void draw(float x, float y, float z);
	private:
		unsigned int componentID;
};

#endif
