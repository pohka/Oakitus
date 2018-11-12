#ifndef SPRITE_H
#define SPRITE_H

using namespace std;
#include <string>
#include "shader_s.h"

#include "Component.h"


class Sprite : public Component
{
	public:
		Sprite(string src, int x, int y, int w, int h);
		~Sprite();
		string getSrc();
		void draw(float x, float y, float z, Shader &ourShader) override;
		unsigned int getTexture();
		unsigned int getVAO();

		int x, y, w, h;
	private:
		string src;
		unsigned int texture, VBO, VAO;
};

#endif