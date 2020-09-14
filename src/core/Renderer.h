#pragma once

#include <memory>
#include <bgfx/bgfx.h>

using std::unique_ptr;

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void init(int32_t width, int32_t height);
    void beginFrame();
    void draw();
    void endFrame();

private:
    bgfx::ProgramHandle programHandle;
    bgfx::DynamicVertexBufferHandle vertexBuffer0;
    bgfx::DynamicIndexBufferHandle indexBuffer0;
};
