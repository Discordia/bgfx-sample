#pragma once

#include <memory>
#include <bgfx/bgfx.h>

using std::unique_ptr;

struct RenderMemory {
    uint8_t* data;
    uint32_t size;

    RenderMemory(const void* data, uint32_t size) {
        this->data = (uint8_t*) data;
        this->size = size;
    }
};

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void init(int32_t width, int32_t height);
    void beginFrame();
    void draw(const RenderMemory *vertices, const RenderMemory *indices);
    void endFrame();

private:
    bgfx::ProgramHandle programHandle;
    bgfx::DynamicVertexBufferHandle vertexBuffer0;
    bgfx::DynamicIndexBufferHandle indexBuffer0;
};
