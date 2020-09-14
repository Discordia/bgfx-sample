#pragma once

#include <bgfx/bgfx.h>
#include <core/RenderChunk.h>

struct PosColorVertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
};

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void init(int32_t width, int32_t height);
    void beginFrame();
    void draw(RenderChunk& renderChunk);
    void endFrame();

private:
    bgfx::ProgramHandle programHandle;
    bgfx::DynamicVertexBufferHandle vertexBuffer0;
    bgfx::DynamicIndexBufferHandle indexBuffer0;
};
