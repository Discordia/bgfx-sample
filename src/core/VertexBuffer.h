#pragma once

#include <bgfx/bgfx.h>
#include <core/VertexTypes.h>

class VertexBuffer {
public:
    VertexBuffer(uint32_t size, VertexType vertexType);
    ~VertexBuffer() = default;

    void bind();
    void update(uint32_t startVertex, const bgfx::Memory *data);

private:
    static bgfx::VertexLayout createVertexLayout(VertexType type);

private:
    bgfx::DynamicVertexBufferHandle vertexBufferHandle{};
};