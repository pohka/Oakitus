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
		virtual void onUpdate();
		virtual void onDraw();

	protected:
		Entity* entity;

	private:
		unsigned int componentID;
		
		
};

#endif