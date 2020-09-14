#include <core/VertexBuffer.h>

VertexBuffer::VertexBuffer(uint32_t size, bgfx::VertexLayout vertexLayout) {
    this->vertexBufferHandle = bgfx::createDynamicVertexBuffer(8, vertexLayout);
}

void VertexBuffer::bind() {
    bgfx::setVertexBuffer(0, vertexBufferHandle);
}

void VertexBuffer::update(uint32_t startVertex, const bgfx::Memory *data) {
    bgfx::update(vertexBufferHandle, startVertex, data);
}
