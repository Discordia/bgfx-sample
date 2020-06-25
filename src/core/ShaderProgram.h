#pragma once

#include <core/StreamFactory.h>
#include <bgfx/bgfx.h>
#include <fstream>

using std::shared_ptr;

class ShaderProgram {
public:
    explicit ShaderProgram(shared_ptr<StreamFactory> streamFactory)
            : streamFactory(std::move(streamFactory)) {}

    bgfx::ProgramHandle loadProgram(const string& vertexShaderFile, const string& fragmentShaderFile) {
        auto vertexShaderHandle = loadShader(vertexShaderFile);
        auto fragmentShaderHandle = loadShader(fragmentShaderFile);
        return bgfx::createProgram(vertexShaderHandle, fragmentShaderHandle, true);
    }

private:
    bgfx::ShaderHandle loadShader(const string& name) {
        char* data = new char[2048];
        auto fileStream = streamFactory->open(name);
        fileStream->read(data, fileStream->size());

        const bgfx::Memory* mem = bgfx::copy(data,fileStream->size() + 1);
        mem->data[mem->size-1] = '\0';

        bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, name.c_str());
        return handle;
    }

private:
    shared_ptr<StreamFactory> streamFactory;
};