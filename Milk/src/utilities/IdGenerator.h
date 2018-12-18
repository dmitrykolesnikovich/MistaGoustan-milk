#ifndef _ID_GENERATOR_
#define _ID_GENERATOR

#include <vector>

class IdGenerator
{
public:
	IdGenerator() = default;

	// Get unique id.
	unsigned int popId();

	// Push id back onto stack for re use.
	void pushId(unsigned int id);

private:
	std::vector<unsigned int> _availableIds;
	unsigned int _count;
};

#endif
