#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
	friend class Entity;
	public:
		Component();
		virtual ~Component();
		static unsigned int getNextID();
		virtual void update();
		virtual void draw();

	protected:
		Entity* entity;

	private:
		unsigned int componentID;
		
		
};

#endif