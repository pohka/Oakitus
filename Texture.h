#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	public:
		Texture(const char* src);
		~Texture();
		unsigned int getID();
		int getWidth();
		int getHeight();
	private:
		unsigned int id;
		int width, height;
};

#endif
