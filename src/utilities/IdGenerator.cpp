#include "IdGenerator.h"

milk::IdGenerator::IdGenerator()
        : count_(0)
{
}

unsigned int milk::IdGenerator::popId()
{
    if (availableIds_.empty())
        return count_++;

    unsigned int id = availableIds_.back();
    availableIds_.pop_back();

    return id;
}

void milk::IdGenerator::pushId(unsigned int id)
{
    for (auto& it : availableIds_)
    {
        // No duplicate ids allowed.
        if (it == id)
            return;
    }

    availableIds_.emplace_back(id);
}
