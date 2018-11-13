#include "IDGenerator.h"
#include <limits.h>

IDGenerator::IDGenerator()
{
	this->count = 0;
}

IDGenerator::~IDGenerator(){}

unsigned int IDGenerator::nextID()
{
	unsigned int id = count;
	if (count == UINT_MAX)
	{
		count = 0;
	}
	else
	{
		count++;
	}
	return id;
}