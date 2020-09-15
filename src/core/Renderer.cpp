#include <core/Renderer.h>
#include <core/StreamFactory.h>
#include <core/Camera.h>

Renderer::Renderer(shared_ptr<StreamFactory> streamFactory, vector<shared_ptr<RenderChunk>> &renderQueue)
        : streamFactory(std::move(streamFactory)), renderQueue(renderQueue) {}

void Renderer::init(int32_t width, int32_t height) {
    // Camera setup
    Camera camera(width, height);
    const bx::Vec3 eye = {0.0f, 0.0f, 10.0f};
    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    camera.setLookAt(eye, at);
    camera.setProjection(60.0f, 0.1f, 100.0f);
    camera.update();

    // Shader program used to render setup
    this->shaderProgram = ShaderProgram::load(streamFactory, "v_simple.bin", "f_simple.bin");

    // VertexBuffer and IndexBuffer setup
    this->vertexBuffer = std::make_unique<VertexBuffer>(20, VertexType::POS3_COLOR4);
    this->indexBuffer = std::make_unique<IndexBuffer>(20);
}

void Renderer::beginFrame() {
}

void Renderer::drawFrame() {
    uint32_t vertexOffset = 0;
    uint32_t indexOffset = 0;
    uint32_t vertexCount = 4;  // set from vertices
    uint32_t drawCount = 6;    // set from indices

    for (const auto &chunk : renderQueue) {
        vertexBuffer->update(vertexOffset, chunk->getGeometry()->getVerticesAsRef());
        indexBuffer->update(indexOffset, chunk->getGeometry()->getIndicesAsRef());

        vertexOffset += vertexCount;
        indexOffset += drawCount;
    }

    vertexBuffer->bind(0, 0, 8);
    indexBuffer->bind(0, 6);
    shaderProgram->submit();

    vertexBuffer->bind(0, 0, 8);
    indexBuffer->bind(6, 6);
    shaderProgram->submit();
}

void Renderer::endFrame() {
    renderQueue.clear();
    bgfx::frame();
}

