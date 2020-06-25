#pragma once

#include <cstdio>
#include <string>
#include <fstream>
#include <bgfx/bgfx.h>

using std::string;

class ShaderProgram {
public:
    static ShaderProgram create(const string& vertexShaderFile, const string& fragmentShaderFile) {
        auto vsh = loadShader(vertexShaderFile);
        auto fsh = loadShader(fragmentShaderFile);
        return ShaderProgram(bgfx::createProgram(vsh, fsh, true));
    }

    bgfx::ProgramHandle getHandle() const {return programHandle;}

private:
    explicit ShaderProgram(bgfx::ProgramHandle programHandle)
        : programHandle(programHandle) {}

    static bgfx::ShaderHandle loadShader(const string& name) {
        char* data = new char[2048];
        std::ifstream file;
        size_t fileSize = 0;
        file.open(name);

        if(file.is_open()) {
            file.seekg(0, std::ios::end);
            fileSize = file.tellg();
            file.seekg(0, std::ios::beg);
            file.read(data, fileSize);
            file.close();
        }

        const bgfx::Memory* mem = bgfx::copy(data,fileSize+1);
        mem->data[mem->size-1] = '\0';
        bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, name.c_str());
        return handle;
    }

private:
    bgfx::ProgramHandle programHandle;
};