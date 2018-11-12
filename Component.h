#ifndef COMPONENT_H
#define COMPONENT_H

#include "shader_s.h"

class Component
{
	public:
		Component();
		virtual ~Component();
		static unsigned int getNextID();
		virtual void draw(float x, float y, float z, Shader& shader);
	private:
		unsigned int componentID;
};

#endif
