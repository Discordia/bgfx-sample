#pragma once

#include "Stream.h"
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class StreamFactory
{
public:
    StreamFactory() {}
    virtual ~StreamFactory() {}

    virtual unique_ptr<Stream> open(const string& fileName) = 0;
};