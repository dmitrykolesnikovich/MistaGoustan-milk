#ifndef MILK_ID_GENERATOR_H
#define MILK_ID_GENERATOR_H

#include <vector>

namespace milk {
    class IdGenerator {
    public:
        IdGenerator();

        // Get unique id.
        unsigned int popId();

        // Push id back onto stack for re use.
        void pushId(unsigned int id);

    private:
        std::vector<unsigned int> availableIds_;
        unsigned int count_;
    };
}

#endif
