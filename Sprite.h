#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "Component.h"
#include "Texture.h"

class Sprite : public Component
{
	public:
		Sprite(std::string src, int x, int y, int w, int h, unsigned int shaderID);
		~Sprite();
		std::string getSrc();
		void draw() override;
		unsigned int getVAO();

		int x, y, w, h;
		unsigned int shaderID;
	private:
		std::string src;
		unsigned int VBO, VAO;
		Texture* texture;
};

#endif