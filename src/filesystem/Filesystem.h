#ifndef MILK_FILESYSTEM_H
#define MILK_FILESYSTEM_H

#include <string>

namespace milk
{
    // File system is responsible for reading the contents of files n' such.
    class Filesystem
    {
    public:
        virtual std::string contents(const std::string& filename) = 0;
    };
}

#endif
