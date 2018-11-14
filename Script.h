#ifndef SCRIPT_H
#define SCRIPT_H

class Entity;

class Script
{
	friend class Entity;
	public:
		Script();
		virtual ~Script();
		virtual void init();
		virtual void onUpdate();
		
	protected:
		Entity* entity;

	private:
		unsigned int scriptID;
		

};

#endif
