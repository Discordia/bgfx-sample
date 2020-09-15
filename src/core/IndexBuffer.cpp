#include <core/IndexBuffer.h>

IndexBuffer::IndexBuffer(uint32_t size) {
    indexBufferHandle = bgfx::createDynamicIndexBuffer(size);
}

void IndexBuffer::bind(uint32_t startIndex, uint32_t indexCount) {
    bgfx::setIndexBuffer(indexBufferHandle, startIndex, indexCount);
}

void IndexBuffer::update(uint32_t startIndex, const bgfx::Memory *data) {
    bgfx::update(indexBufferHandle, startIndex, data);
}

