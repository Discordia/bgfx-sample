#pragma once

#include <bgfx/bgfx.h>
#include <core/VertexTypes.h>

class VertexBuffer {
public:
    VertexBuffer(uint32_t size, VertexType vertexType);
    ~VertexBuffer() = default;

    void bind(uint8_t stream, uint32_t startVertex, uint32_t vertexCount);
    void update(uint32_t startVertex, const bgfx::Memory *data);

private:
    static bgfx::VertexLayout createVertexLayout(VertexType type);

private:
    bgfx::DynamicVertexBufferHandle vertexBufferHandle{};
};