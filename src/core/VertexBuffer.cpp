#include <core/VertexBuffer.h>

VertexBuffer::VertexBuffer(uint32_t size, VertexType vertexType) {
    bgfx::VertexLayout vertexLayout = createVertexLayout(vertexType);
    this->vertexBufferHandle = bgfx::createDynamicVertexBuffer(size, vertexLayout);
}

void VertexBuffer::bind() {
    bgfx::setVertexBuffer(0, vertexBufferHandle);
}

void VertexBuffer::update(uint32_t startVertex, const bgfx::Memory *data) {
    bgfx::update(vertexBufferHandle, startVertex, data);
}

bgfx::VertexLayout VertexBuffer::createVertexLayout(VertexType type) {
    bgfx::VertexLayout vertexLayout;

    switch (type) {
        case POS3_COLOR4:
            vertexLayout
                    .begin()
                    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                    .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
                    .end();
    }

    return vertexLayout;
}
