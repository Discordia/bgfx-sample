#pragma once

#include <core/StreamFactory.h>
#include <bgfx/bgfx.h>
#include <fstream>

using std::shared_ptr;

class ShaderProgram {
public:
    explicit ShaderProgram(bgfx::ProgramHandle programHandle)
            : programHandle(programHandle) {}

    ~ShaderProgram() = default;

    static unique_ptr<ShaderProgram> load(
            const shared_ptr<StreamFactory>& streamFactory,
            const string& vertexShaderFile,
            const string& fragmentShaderFile) {
        auto vertexShaderHandle = loadShader(streamFactory, vertexShaderFile);
        auto fragmentShaderHandle = loadShader(streamFactory, fragmentShaderFile);
        return std::make_unique<ShaderProgram>(bgfx::createProgram(vertexShaderHandle, fragmentShaderHandle, true));
    }

    void submit() {
        bgfx::submit(0, programHandle);
    }

private:
    static bgfx::ShaderHandle loadShader(const shared_ptr<StreamFactory>& streamFactory, const string& name) {
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
    bgfx::ProgramHandle programHandle;
};