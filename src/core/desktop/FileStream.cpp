#include "FileStream.h"

using std::ifstream;
using std::ios;

FileStream::FileStream(const string& path)
        : file(path.c_str(), ios::binary), fileSize(0)
{
    if (file && file.is_open())
    {
        file.seekg(0, ios::end);
        this->fileSize = file.tellg();
        file.seekg(0, file.beg);
    }
}

FileStream::~FileStream()
{
    file.close();
}

unsigned int FileStream::size() const
{
    return fileSize;
}

int FileStream::read(void* target, const size_t bytes)
{
    file.read((char*) target, bytes);

    int readBytes = bytes;

    if (file.fail())
    {
        readBytes = -1;
    }

    return readBytes;
}