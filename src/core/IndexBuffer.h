#pragma once

#include <bgfx/bgfx.h>

class IndexBuffer {
public:
    explicit IndexBuffer(uint32_t size);

    void bind();
    void update(uint32_t startIndex, const bgfx::Memory * data);

private:
    bgfx::DynamicIndexBufferHandle indexBufferHandle{};
};

