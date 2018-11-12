#ifndef GAME_H
#define GAME_H

#include "Oakitus.h"

class Game {
	public:
		static void load(Oakitus* engine);
		static void init();
		static void update();
		static void draw();
};

#endif