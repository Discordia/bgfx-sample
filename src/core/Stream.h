#pragma once

#include <cstddef>

using std::size_t;

class Stream
{
public:
    virtual ~Stream() = default;
    virtual unsigned int size() const = 0;
    virtual int read(void* target, size_t bytes) = 0;
};