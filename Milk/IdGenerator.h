#pragma once

#include <stack>

class IdGenerator
{
public:
	IdGenerator();
	~IdGenerator();

	unsigned int popId();

	void pushId(unsigned int id);

private:
	std::stack<unsigned int> _availableIds;
	unsigned int _count;

};
