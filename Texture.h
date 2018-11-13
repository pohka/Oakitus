#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
	public:
		Texture(const char* src);
		~Texture();
		unsigned int getID();

	private:
		unsigned int id;
};

#endif
