#ifndef SPRITE_H
#define SPRITE_H

using namespace std;
#include <string>
#include "shader_s.h"



class Sprite
{
	public:
		Sprite(string src, int x, int y, int w, int h);
		~Sprite();
		string getSrc();
		void draw(float x, float y, float z, Shader &ourShader);
		unsigned int getTexture();
		unsigned int getVAO();

		int x, y, w, h;
	private:
		string src;
		unsigned int texture, VBO, VAO;
};

#endif