#ifndef _ID_GENERATOR_
#define _ID_GENERATOR

#include <vector>

class IdGenerator
{
public:
	IdGenerator() = default;

	unsigned int popId();

	void pushId(unsigned int id);

private:
	std::vector<unsigned int> _availableIds;
	unsigned int _count;
};

#endif
