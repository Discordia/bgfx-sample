#pragma once

#include <core/StreamFactory.h>
#include "FileStream.h"

class DesktopStreamFactory : public StreamFactory
{
public:

    DesktopStreamFactory(const string& directoryName)
        : directoryName(directoryName) {}

    unique_ptr<Stream> open(const string& fileName) override;

private:
    string directoryName;
};

unique_ptr<Stream> DesktopStreamFactory::open(const string& fileName)
{
    return unique_ptr<Stream>(new FileStream(directoryName + "/" + fileName));
}
