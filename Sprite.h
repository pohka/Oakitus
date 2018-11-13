#ifndef SPRITE_H
#define SPRITE_H

using namespace std;
#include <string>

#include "Component.h"


class Sprite : public Component
{
	public:
		Sprite(string src, int x, int y, int w, int h, unsigned int shaderID);
		~Sprite();
		string getSrc();
		void draw() override;
		unsigned int getTexture();
		unsigned int getVAO();

		int x, y, w, h;
		unsigned int shaderID;
	private:
		string src;
		unsigned int texture, VBO, VAO;
};

#endif