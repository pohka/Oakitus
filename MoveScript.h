#ifndef MOVE_SCRIPT_H
#define MOVE_SCRIPT_H

#include "Script.h"

class MoveScript : public Script
{
	public :
		MoveScript();
		~MoveScript();
		void update(Entity* ent) override;
};

#endif