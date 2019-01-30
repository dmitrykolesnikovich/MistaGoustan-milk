#ifndef MILK_FILESYSTEMADAPTER_H
#define MILK_FILESYSTEMADAPTER_H

#include "filesystem/Filesystem.h"

namespace milk
{
    namespace adapter
    {
        class FilesystemAdapter : public Filesystem
        {
        public:
            explicit FilesystemAdapter(std::string rootDir);

            std::string contents(const std::string& filename) override;

        private:
            std::string rootDir_;
        };
    }
}


#endif
