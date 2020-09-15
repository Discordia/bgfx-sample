#pragma once

#include <bgfx/bgfx.h>

class IndexBuffer {
public:
    explicit IndexBuffer(uint32_t size);

    void bind(uint32_t startIndex, uint32_t indexCount);
    void update(uint32_t startIndex, const bgfx::Memory * data);

private:
    bgfx::DynamicIndexBufferHandle indexBufferHandle{};
};

