#pragma once

#include <memory>
#include <bgfx/bgfx.h>
#include <core/RenderChunk.h>
#include <core/ShaderProgram.h>
#include <core/VertexBuffer.h>
#include <core/IndexBuffer.h>

class StreamFactory;

using std::unique_ptr;
using std::shared_ptr;

struct PosColorVertex {
    float x;
    float y;
    float z;
    uint32_t abgr;
};

class Renderer {
public:
    explicit Renderer(shared_ptr<StreamFactory>);
    ~Renderer() = default;

    void init(int32_t width, int32_t height);
    void beginFrame();
    void draw(RenderChunk& renderChunk);
    void endFrame();

private:
    shared_ptr<StreamFactory> streamFactory;
    unique_ptr<ShaderProgram> shaderProgram;
    unique_ptr<VertexBuffer> vertexBuffer;
    unique_ptr<IndexBuffer> indexBuffer;
};
