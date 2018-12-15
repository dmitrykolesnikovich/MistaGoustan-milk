#include "IdGenerator.h"



IdGenerator::IdGenerator()
{
}

IdGenerator::~IdGenerator()
{
}

unsigned int IdGenerator::popId()
{
	if (_availableIds.empty())
		return _count++;

	unsigned int id = _availableIds.top();
	_availableIds.pop();

	return id;
}

void IdGenerator::pushId(unsigned int id)
{
	if ()
}
