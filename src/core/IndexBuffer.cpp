#include <core/IndexBuffer.h>

IndexBuffer::IndexBuffer(uint32_t size) {
    indexBufferHandle = bgfx::createDynamicIndexBuffer(12);
}

void IndexBuffer::bind() {
    bgfx::setIndexBuffer(indexBufferHandle);
}

void IndexBuffer::update(uint32_t startIndex, const bgfx::Memory *data) {
    bgfx::update(indexBufferHandle, startIndex, data);
}

