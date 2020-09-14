#pragma once

#include <bgfx/bgfx.h>

class VertexBuffer {
public:
    VertexBuffer(uint32_t size, bgfx::VertexLayout vertexLayout);
    ~VertexBuffer() = default;

    void bind();
    void update(uint32_t startVertex, const bgfx::Memory *data);

private:
    bgfx::DynamicVertexBufferHandle vertexBufferHandle{};
};