#pragma once

#include <core/Stream.h>

#include <fstream>
#include <string>

using std::string;
using std::ifstream;

class FileStream : public Stream
{
public:
    explicit FileStream(const string& path);
    ~FileStream() override;

    unsigned int size() const override;
    int read(void* target, size_t bytes) override;

private:
    ifstream file;
    unsigned int fileSize;
};