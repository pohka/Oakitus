#ifndef ID_GENERATOR_H
#define ID_GENERATOR_H

class IDGenerator
{
	public:
		IDGenerator();
		~IDGenerator();
		unsigned int nextID();
	private:
		unsigned int count;
};
#endif
