#include "IdGenerator.h"

IdGenerator::IdGenerator()
{
}

unsigned int IdGenerator::popId()
{
	if (_availableIds.empty())
		return _count++;

	unsigned int id = _availableIds.back();
	_availableIds.pop_back();

	return id;
}

void IdGenerator::pushId(unsigned int id)
{
	for (auto& it : _availableIds)
	{
		if (it == id)
			return;
	}

	_availableIds.emplace_back(id);
}
